#pragma once

#include <iostream>

namespace cookie {
    class string {
        private:
            char*           _data = nullptr;
            unsigned long   _size = 0;

        public:
            string() noexcept;
            string(const int size);
            string(const char* c_string);

            string(const string& ref);
            string(string&& ref);

            string& operator=(const string& ref);
            string& operator=(string&& ref) noexcept;

            string operator+(const string& rhs) const;
            string& operator+=(const string& rhs);

            string operator,(const string& rhs) const;

            const char* data() const;

            ~string();
    };

    std::ostream& operator<<(std::ostream& os, const string& string);
}