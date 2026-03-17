#pragma once

#include <string>
#include <map>
#include <linux/gpio.h>

namespace cookie::gpio {
    class Chip {
        public:
            explicit Chip(const std::string& name);
            ~Chip();

            void add_line_request(int number, const std::string& consumer, bool output);
            void send_line_value(int number, bool value) const;
        private:
            int _fd;
            std::map<int, gpio_v2_line_request> _line_fd;
    };
};
