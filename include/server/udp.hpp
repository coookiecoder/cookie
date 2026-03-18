#pragma once

#include <string>
#include <functional>
#include <map>
#include <atomic>
#include <thread>
#include <list>

#include <netinet/in.h>

namespace cookie::server {
    class udp {
    public:
        explicit udp(int port = 5000);

        void map_response(const std::string& command, std::function<std::string(std::string, sockaddr_in)> callback);
        void unmap_response(const std::string& command);

        void map_response_word(const std::string& command, std::function<std::string(std::string, sockaddr_in)> callback);
        void unmap_response_word(const std::string& command);

        void map_default(std::function<std::string(std::string, sockaddr_in)> callback);

        void start();
        void stop();

        void broadcast(const std::string& message) const;
        void remove_client(const sockaddr_in& client_address);

        ~udp();

        std::list<sockaddr_in> client_addresses;

    private:
        int _port = 0;
        int _socket = 0;
        int _socket_option = 1;
        sockaddr_in _server_address = {};

        std::map<std::string, std::function<std::string(std::string, sockaddr_in)>> _callbacks;
        std::map<std::string, std::function<std::string(std::string, sockaddr_in)>> _callbacks_word;
        std::function<std::string(std::string, sockaddr_in)> _default_callback;

        std::atomic<bool> _is_running;

        std::thread _server_thread;

        void _run();
    };
}