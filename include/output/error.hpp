#pragma once

#include <iostream>

namespace cookie::output {
    class Error {
    public:
        Error() = default;
        ~Error() = default;

        Error& operator<<(const std::string& message);
        Error& operator<<(const char* message);

        Error& operator<<(std::ostream& (*manipulator)(std::ostream&));
    };

    inline Error error;
};
