#include <client/tcp.hpp>

#include <stdexcept>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <thread>

#include <arpa/inet.h>

std::string place_holder_client(std::string) {
    return "";
}

namespace cookie::client {
    tcp::tcp(const char * ip, const int port) {
        this->_port = port;
        this->_socket = socket(AF_INET, SOCK_STREAM, 0);

        if (this->_socket == -1) {
            throw std::runtime_error(__PRETTY_FUNCTION__ + std::string(": socket()"));
        }

        if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &this->_socket_option, sizeof(this->_socket_option))) {
            throw std::runtime_error(__PRETTY_FUNCTION__ + std::string(": setsockopt()"));
        }

        this->_server_address.sin_family = AF_INET;
        this->_server_address.sin_port = htons(this->_port);

        if (inet_pton(AF_INET, ip, &this->_server_address.sin_addr) <= 0) {
            throw std::runtime_error(__PRETTY_FUNCTION__ + std::string(": inet_pton()"));
        }

        this->_default_callback = place_holder_client;
    }

    void tcp::map_response(const std::string& command, std::function<std::string(std::string)> callback) {
        this->_callbacks[command] = std::move(callback);
    }

    void tcp::unmap_response(const std::string& command) {
        _callbacks.erase(command);
    }

    void tcp::map_default(std::function<std::string(std::string)> callback) {
        this->_default_callback = std::move(callback);
    }

    void tcp::start() {
        if (_is_running) {
            throw std::runtime_error(__PRETTY_FUNCTION__ + std::string(": start()"));
        }

        if (connect(this->_socket, reinterpret_cast<sockaddr*>(&this->_server_address), sizeof(this->_server_address)) < 0) {
            throw std::runtime_error(__PRETTY_FUNCTION__ + std::string(": connect()"));
        }
        _is_running = true;

        _client_thread = std::thread([this] {this->_run();});
    }

    void tcp::stop() {
        if (_is_running == false) {
            return;
        }

        _is_running = false;

        shutdown(_socket, SHUT_RDWR);

        if (_client_thread.joinable()) {
            _client_thread.join();
        }
    }


    void tcp::send(const std::string& message) {
        if (::send(this->_socket, message.c_str(), message.size(), MSG_NOSIGNAL) < 0) {
            this->stop();
            throw std::runtime_error(__PRETTY_FUNCTION__ + std::string(": send()"));
        }
    }

    tcp::~tcp() {
        stop();
        close(this->_socket);
    }

    void tcp::_run() {
        while (_is_running) {
            char buffer[1024];
            ssize_t bytes_read = recv(this->_socket, buffer, sizeof(buffer) - 1, 0);

            if (bytes_read > 0) {
                buffer[bytes_read] = '\0';
                std::string command(buffer);
                std::erase(command, '\n');
                std::erase(command, '\r');

                if (auto it = _callbacks.find(command); it != _callbacks.end()) {
                    if (std::string response = it->second(command); !response.empty())
                        this->send(response);
                } else {
                    if (std::string response = _default_callback(command); !response.empty())
                        this->send(response);
                }
            } else {
                _is_running = false;
                break;
            }
        }
    }
}

