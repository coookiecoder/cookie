#include <gpio/chip.hpp>

#ifdef __linux__

#include <cstring>
#include <stdexcept>

#include <fcntl.h>
#include <unistd.h>
#include <linux/gpio.h>
#include <sys/ioctl.h>

namespace cookie::gpio {
    Chip::Chip(const std::string &name) {
        this->_fd = open(name.c_str(), O_RDWR);

        if (this->_fd == -1) {
            throw std::runtime_error("Chip name not found");
        }
    }

    Chip::~Chip() {
        close(this->_fd);
    }

    void Chip::add_line_request(const int number, const std::string &consumer, const bool output) {
        gpio_v2_line_request request = {};

        request.num_lines = 1;
        request.offsets[0] = number;

        if (output)
            request.config.flags = GPIO_V2_LINE_FLAG_OUTPUT;
        else
            request.config.flags = GPIO_V2_LINE_FLAG_INPUT;

        if (consumer.size() > GPIO_MAX_NAME_SIZE)
            throw std::runtime_error("Consumer name too big");

        strcpy(request.consumer, consumer.c_str());

        if (ioctl(this->_fd, GPIO_V2_GET_LINE_IOCTL, &request) < 0)
            throw std::runtime_error("IOCTL error");

        this->_line_fd.emplace(number, request);
    }

    void Chip::send_line_value(const int number, const bool value) const {
        gpio_v2_line_values values = {};

        values.mask = 1;
        values.bits = value;

        ioctl(this->_line_fd.find(number)->second.fd, GPIO_V2_LINE_SET_VALUES_IOCTL, &values);
    }
}

#endif