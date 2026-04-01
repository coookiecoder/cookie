#pragma once

#include <string>

namespace cookie::gpio {
    class Pwm {
        public:
            explicit Pwm(int pwm);
            ~Pwm() = default;

            void export_channel(int channel) const;

            void set_period(int channel, int period) const;
            void set_duty_cycle(int channel, int duty_cycle) const;
            void enable(int channel) const;
            void disable(int channel) const;

        private:
            std::string chip_path;
    };
}
