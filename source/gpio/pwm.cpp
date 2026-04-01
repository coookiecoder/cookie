#include <gpio/pwm.hpp>

#include <fstream>

namespace cookie::gpio {
    Pwm::Pwm(const int pwm) {
        this->chip_path = "/sys/class/pwm/pwmchip";
        this->chip_path += std::to_string(pwm);
    }

    void Pwm::export_channel(const int channel) const {
        std::ofstream export_file(this->chip_path + "/export");
        export_file << std::to_string(channel);
        export_file.close();
    }

    void Pwm::set_period(const int channel, const int period) const {
        std::ofstream period_file(this->chip_path + "/period");
        period_file << std::to_string(period);
        period_file.close();
    }

    void Pwm::set_duty_cycle(const int channel, const int duty_cycle) const {
        std::ofstream duty_cycle_file(this->chip_path + "/pwm" + std::to_string(channel) + "/duty_cycle");
        duty_cycle_file << std::to_string(duty_cycle);
        duty_cycle_file.close();
    }

    void Pwm::enable(const int channel) const {
        std::ofstream enable_file(this->chip_path + "/pwm" + std::to_string(channel) + "/enable");
        enable_file << "1";
        enable_file.close();
    }

    void Pwm::disable(const int channel) const {
        std::ofstream disable_file(this->chip_path + "/pwm" + std::to_string(channel) + "/disable");
        disable_file << "0";
        disable_file.close();
    }
}
