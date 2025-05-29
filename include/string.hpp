#pragma once

#include <iostream>

namespace cookie {
    class string {
        private:
            char*           _data = nullptr;
            unsigned long   _size = 0;

        public:
            explicit string() noexcept;
            explicit string(unsigned int size);
            explicit string(const char* c_string);

            string(const string& ref);
            string(string&& ref) noexcept;

            string& operator=(const string& ref);
            string& operator=(string&& ref) noexcept;
            string& operator=(const char* string);

            string& operator+=(const string& rhs);
            string& operator+=(const char* rhs);

            [[nodiscard]] const char* data() const;
            [[nodiscard]] unsigned long size() const;

            ~string();
    };

    std::ostream& operator<<(std::ostream& os, const string& string);
    std::istream& operator>>(std::istream& is, string& string);

    bool operator==(const string& lhs, const string& rhs);
    bool operator==(const string& lhs, const char* rhs);
    bool operator==(const char* lhs, const string& rhs);

    bool operator!=(const string& lhs, const string& rhs);
    bool operator!=(const string& lhs, const char* rhs);
    bool operator!=(const char* lhs, const string& rhs);

    string operator+(const string& lhs, const string& rhs);
    string operator+(const string& lhs, const char* rhs);
    string operator,(const string& lhs, const string& rhs);
    string operator,(const string& lhs, const char* rhs);

    unsigned long strlen(const string& string);
    unsigned long strlen(const char* string);
}