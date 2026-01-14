#include <client/udp.hpp>

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
    udp::udp(const char * ip, const int port) {
        this->_port = port;
        this->_socket = socket(AF_INET, SOCK_DGRAM, 0);

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

    void udp::map_response(const std::string& command, std::function<std::string(std::string)> callback) {
        this->_callbacks[command] = std::move(callback);
    }

    void udp::unmap_response(const std::string& command) {
        _callbacks.erase(command);
    }

    void udp::map_default(std::function<std::string(std::string)> callback) {
        this->_default_callback = std::move(callback);
    }

    void udp::start() {
        if (_is_running) {
            throw std::runtime_error(__PRETTY_FUNCTION__ + std::string(": start()"));
        }

        _is_running = true;

        _client_thread = std::thread([this] {this->_run();});
    }

    void udp::stop() {
        if (_is_running == false) {
            return;
        }

        _is_running = false;

        shutdown(_socket, SHUT_RDWR);

        if (_client_thread.joinable()) {
            _client_thread.join();
        }
    }


    void udp::send(const std::string& message) {
        sendto(this->_socket, message.c_str(), message.size(), 0, reinterpret_cast<struct sockaddr*>(&this->_server_address), sizeof(this->_server_address));
    }

    udp::~udp() {
        stop();
        close(this->_socket);
    }

    void udp::_run() {
        while (_is_running) {
            char buffer[1024];
            ssize_t bytes_read = recvfrom(this->_socket, buffer, sizeof(buffer) - 1, 0, nullptr, nullptr);

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

