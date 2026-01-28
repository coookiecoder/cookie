#include <server/tcp.hpp>

#include <stdexcept>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <thread>

std::string place_holder_server(std::string str) {
    return str;
}

namespace cookie::server {
    tcp::tcp(const int port) : _is_running(false) {
        this->_port = port;
        this->_socket = socket(AF_INET, SOCK_STREAM, 0);

        if (this->_socket == -1) {
            throw std::runtime_error(__PRETTY_FUNCTION__ + std::string(": socket()"));
        }

        if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &this->_socket_option, sizeof(this->_socket_option))) {
            throw std::runtime_error(__PRETTY_FUNCTION__ + std::string(": setsockopt()"));
        }

        this->_server_address.sin_family = AF_INET;
        this->_server_address.sin_addr.s_addr = INADDR_ANY;
        this->_server_address.sin_port = htons(this->_port);

        if (bind(this->_socket, reinterpret_cast<sockaddr *>(&this->_server_address), sizeof(this->_server_address)) < 0) {
            close(this->_socket);
            throw std::runtime_error(__PRETTY_FUNCTION__ + std::string(": bind()"));
        }

        if (listen(this->_socket, SOMAXCONN) < 0) {
            close(this->_socket);
            throw std::runtime_error(__PRETTY_FUNCTION__ + std::string(": listen()"));
        }

        this->_default_callback = place_holder_server;
    }

    void tcp::map_response(const std::string& command, std::function<std::string(std::string)> callback) {
        _callbacks[command] = std::move(callback);
    }

    void tcp::unmap_response(const std::string& command) {
        _callbacks.erase(command);
    }

    void tcp::map_response_word(const std::string& command, std::function<std::string(std::string)> callback) {
        this->_callbacks_word[command] = std::move(callback);
    }

    void tcp::unmap_response_word(const std::string& command) {
        _callbacks_word.erase(command);
    }

    void tcp::map_default(std::function<std::string(std::string)> callback) {
        _default_callback = std::move(callback);
    }

    void tcp::start() {
        if (_is_running) {
            throw std::runtime_error(__PRETTY_FUNCTION__ + std::string(": start()"));
        }

        _is_running = true;

        _server_thread = std::thread([this] {this->_run();});
    }
    
    void tcp::stop() {
        if (_is_running == false) {
            return;
        }

        _is_running = false;

        shutdown(_socket, SHUT_RDWR);

        if (_server_thread.joinable()) {
            _server_thread.join();
        }

        for (const int client_socket : _client_sockets) {
            close(client_socket);
        }
        _client_sockets.clear();
    }

    tcp::~tcp() {
        stop();
        close(this->_socket);
    }

    void tcp::_run() {
        fd_set read_fds;
        char buffer[SOMAXCONN];

        while (_is_running) {
            FD_ZERO(&read_fds);
            FD_SET(_socket, &read_fds);
            int max_fd = _socket;
            for (const int client_socket : _client_sockets) {
                FD_SET(client_socket, &read_fds);
                if (client_socket > max_fd) {
                    max_fd = client_socket;
                }
            }

            timeval timeout = {1 ,0};

            if (const int activity = select(max_fd + 1, &read_fds, nullptr, nullptr, &timeout); activity < 0 && errno != EINTR) {
                continue;
            }

            if (FD_ISSET(_socket, &read_fds)) {
                if (int new_socket = accept(_socket, nullptr, nullptr); new_socket >= 0) {
                    _client_sockets.push_back(new_socket);
                }
            }

            for (int i = 0; i < _client_sockets.size(); ++i) {
                if (const int client_socket = _client_sockets[i]; FD_ISSET(client_socket, &read_fds)) {
                    if (const long bytes_read = read(client_socket, buffer, sizeof(buffer) - 1); bytes_read <= 0) {
                        close(client_socket);
                        _client_sockets.erase(_client_sockets.begin() + i);
                        --i;
                    } else
                    {
                        buffer[bytes_read] = '\0';
                        std::string command(buffer);
                        std::erase(command, '\n');
                        std::erase(command, '\r');

                        if (auto it = _callbacks.find(command); it != _callbacks.end()) {
                            std::string response = it->second(command);
                            send(client_socket, response.c_str(), response.length(), 0);
                            continue;
                        }

                        std::string command_word = command.substr(0, command.find(' '));

                        if (auto it = _callbacks_word.find(command_word); it != _callbacks_word.end()) {
                            std::string response = it->second(command);
                            send(client_socket, response.c_str(), response.length(), 0);
                            continue;
                        }

                        if (std::string response = _default_callback(command); !response.empty()) {
                            send(client_socket, response.c_str(), response.length(), 0);
                        }
                    }
                }
            }
       }
    }
}
