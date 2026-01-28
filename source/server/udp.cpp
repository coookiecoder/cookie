#include <server/udp.hpp>

#include <stdexcept>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <thread>

std::string place_holder_server(std::string str) {
    return str;
}

namespace cookie::server {
    udp::udp(const int port) : _is_running(false) {
        this->_port = port;
        this->_socket = socket(AF_INET, SOCK_DGRAM, 0);

        if (this->_socket == -1) {
            throw std::runtime_error(__PRETTY_FUNCTION__ + std::string(": socket()"));
        }

        if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &this->_socket_option, sizeof(this->_socket_option))) {
            throw std::runtime_error(__PRETTY_FUNCTION__ + std::string(": setsockopt()"));
        }

        timeval read_timeout = {};
        read_timeout.tv_sec = 1;
        read_timeout.tv_usec = 0;

        if (setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, (&read_timeout), sizeof(read_timeout)) < 0) {
            throw std::runtime_error(__PRETTY_FUNCTION__ + std::string(": setsockopt()"));
        }

        this->_server_address.sin_family = AF_INET;
        this->_server_address.sin_addr.s_addr = INADDR_ANY;
        this->_server_address.sin_port = htons(this->_port);

        if (bind(this->_socket, reinterpret_cast<sockaddr *>(&this->_server_address), sizeof(this->_server_address)) < 0) {
            close(this->_socket);
            throw std::runtime_error(__PRETTY_FUNCTION__ + std::string(": bind()"));
        }

        this->_default_callback = place_holder_server;
    }

    void udp::map_response(const std::string& command, std::function<std::string(std::string)> callback) {
        _callbacks[command] = std::move(callback);
    }

    void udp::unmap_response(const std::string& command) {
        _callbacks.erase(command);
    }

    void udp::map_response_word(const std::string& command, std::function<std::string(std::string)> callback) {
        this->_callbacks_word[command] = std::move(callback);
    }

    void udp::unmap_response_word(const std::string& command) {
        _callbacks_word.erase(command);
    }

    void udp::map_default(std::function<std::string(std::string)> callback) {
        _default_callback = std::move(callback);
    }

    void udp::start() {
        if (_is_running) {
            throw std::runtime_error(__PRETTY_FUNCTION__ + std::string(": start()"));
        }

        _is_running = true;

        _server_thread = std::thread([this] {this->_run();});
    }
    
    void udp::stop() {
        if (_is_running == false) {
            return;
        }

        _is_running = false;

        if (_server_thread.joinable()) {
            _server_thread.join();
        }
    }

    udp::~udp() {
        stop();
        close(this->_socket);
    }

    void udp::_run() {
        char buffer[SOMAXCONN];
        sockaddr_in client_address{};
        socklen_t client_length = sizeof(client_address);

        while (_is_running) {
            const long bytes_read = recvfrom(_socket, buffer, sizeof(buffer) - 1, 0, reinterpret_cast<sockaddr *>(&client_address), &client_length);

            if (bytes_read <= 0) {
                continue;
            }

            buffer[bytes_read] = '\0';
            std::string command(buffer);
            std::erase(command, '\n');
            std::erase(command, '\r');

            if (auto it = _callbacks.find(command); it != _callbacks.end()) {
                std::string response = it->second(command);
                sendto(_socket, response.c_str(), response.length(), 0, reinterpret_cast<sockaddr *>(&client_address), client_length);
                continue;
            }

            std::string command_word = command.substr(0, command.find(' '));

            if (auto it = _callbacks_word.find(command_word); it != _callbacks_word.end()) {
                std::string response = it->second(command);
                sendto(_socket, response.c_str(), response.length(), 0, reinterpret_cast<sockaddr *>(&client_address), client_length);
                continue;
            }

            if (std::string response = _default_callback(command); !response.empty()) {
                sendto(_socket, response.c_str(), response.length(), 0, reinterpret_cast<sockaddr *>(&client_address), client_length);
            }
       }
    }
}