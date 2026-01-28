#pragma once

#include <string>
#include <functional>
#include <map>
#include <vector>
#include <atomic>
#include <thread>

#include <netinet/in.h>

namespace cookie::client {
    class tcp {
    public:
        explicit tcp(const char * ip = "127.0.0.1", int port = 5000);

        void map_response(const std::string& command, std::function<std::string(std::string)> callback);
        void unmap_response(const std::string& command);

        void map_response_word(const std::string& command, std::function<std::string(std::string)> callback);
        void unmap_response_word(const std::string& command);

        void map_default(std::function<std::string(std::string)> callback);

        void start();
        void stop();

        void send(const std::string& message);

        ~tcp();

    private:
        int _port = 0;
        int _socket = 0;
        int _socket_option = 1;
        sockaddr_in _server_address = {};

        std::map<std::string, std::function<std::string(std::string)>> _callbacks;
        std::map<std::string, std::function<std::string(std::string)>> _callbacks_word;
        std::function<std::string(std::string)> _default_callback;

        std::atomic<bool> _is_running = false;

        std::thread _client_thread;

        void _run();
    };
}

