#pragma once

#include <netinet/in.h>
#include <string>
#include <functional>
#include <map>
#include <atomic>
#include <thread>

namespace cookie::server {
    class udp {
    public:
        explicit udp(int port = 5000);

        void map_response(const std::string& command, std::function<std::string(std::string)> callback);
        void unmap_response(const std::string& command);

        void map_default(std::function<std::string(std::string)> callback);

        void start();
        void stop();

        ~udp();

    private:
        int _port = 0;
        int _socket = 0;
        int _socket_option = 1;
        sockaddr_in _server_address = {};

        std::map<std::string, std::function<std::string(std::string)>> _callbacks;
        std::function<std::string(std::string)> _default_callback;

        std::atomic<bool> _is_running;

        std::thread _server_thread;

        void _run();
    };
}