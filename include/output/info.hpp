#pragma once

#include <iostream>

namespace cookie::output {
    class Info {
        public:
            Info() = default;
            ~Info() = default;

            Info& operator<<(const std::string& message);
            Info& operator<<(const char* message);

            Info& operator<<(std::ostream& (*manipulator)(std::ostream&));
    };

    inline Info info;
};
