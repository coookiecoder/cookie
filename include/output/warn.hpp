#pragma once

#include <iostream>

namespace cookie::output {
    class Warn {
    public:
        Warn() = default;
        ~Warn() = default;

        Warn& operator<<(const std::string& message);
        Warn& operator<<(const char* message);

        Warn& operator<<(std::ostream& (*manipulator)(std::ostream&));
    };

    inline Warn warn;
};
