#pragma once

#include <map>
#include <string>

namespace cookie {
    class ArgumentParser {
        public:
            ArgumentParser() = default;
            ~ArgumentParser() = default;

            void parse(int argc, const char** argv);

            void add_needed_string(const std::string& key, std::string& value) {this->need_string.insert({key, value});}

            void add_needed_short(const std::string& key, short& value) {this->need_short.insert({key, value});}
            void add_needed_int(const std::string& key, int& value) {this->need_int.insert({key, value});}
            void add_needed_long(const std::string& key, long& value) {this->need_long.insert({key, value});}
            void add_needed_long_long(const std::string& key, long long& value) {this->need_long_long.insert({key, value});}

            void add_needed_unsigned_short(const std::string& key, unsigned short& value) {this->need_unsigned_short.insert({key, value});}
            void add_needed_unsigned_int(const std::string& key, unsigned int& value) {this->need_unsigned_int.insert({key, value});}
            void add_needed_unsigned_long(const std::string& key, unsigned long& value) {this->need_unsigned_long.insert({key, value});}
            void add_needed_unsigned_long_long(const std::string& key, unsigned long long& value) {this->need_unsigned_long_long.insert({key, value});}

            void add_needed_float(const std::string& key, float& value) {this->need_float.insert({key, value});}
            void add_needed_double(const std::string& key, double& value) {this->need_double.insert({key, value});}

            void add_needed_char(const std::string& key, char& value) {this->need_char.insert({key, value});}
            void add_needed_unsigned_char(const std::string& key, unsigned char& value) {this->need_unsigned_char.insert({key, value});}

            void add_needed_bool(const std::string& key, bool& value) {this->need_bool.insert({key, value});}

            void add_optional_string(const std::string& key, std::string& value) {this->optional_string.insert({key, value});}

            void add_optional_short(const std::string& key, short& value) {this->optional_short.insert({key, value});}
            void add_optional_int(const std::string& key, int& value) {this->optional_int.insert({key, value});}
            void add_optional_long(const std::string& key, long& value) {this->optional_long.insert({key, value});}
            void add_optional_long_long(const std::string& key, long long& value) {this->optional_long_long.insert({key, value});}

            void add_optional_unsigned_short(const std::string& key, unsigned short& value) {this->optional_unsigned_short.insert({key, value});}
            void add_optional_unsigned_int(const std::string& key, unsigned int& value) {this->optional_unsigned_int.insert({key, value});}
            void add_optional_unsigned_long(const std::string& key, unsigned long& value) {this->optional_unsigned_long.insert({key, value});}
            void add_optional_unsigned_long_long(const std::string& key, unsigned long long& value) {this->optional_unsigned_long_long.insert({key, value});}

            void add_optional_float(const std::string& key, float& value) {this->optional_float.insert({key, value});}
            void add_optional_double(const std::string& key, double& value) {this->optional_double.insert({key, value});}

            void add_optional_char(const std::string& key, char& value) {this->optional_char.insert({key, value});}
            void add_optional_unsigned_char(const std::string& key, unsigned char& value) {this->optional_unsigned_char.insert({key, value});}

            void add_optional_bool(const std::string& key, bool& value) {this->optional_bool.insert({key, value});}

        private:
            bool parse_needed(const std::string& current, const std::string& next);
            bool parse_optional(const std::string& current, const std::string& next);

            std::map<std::string, std::string&> need_string;

            std::map<std::string, short&> need_short;
            std::map<std::string, int&> need_int;
            std::map<std::string, long&> need_long;
            std::map<std::string, long long&> need_long_long;

            std::map<std::string, unsigned short&> need_unsigned_short;
            std::map<std::string, unsigned int&> need_unsigned_int;
            std::map<std::string, unsigned long&> need_unsigned_long;
            std::map<std::string, unsigned long long&> need_unsigned_long_long;

            std::map<std::string, float&> need_float;
            std::map<std::string, double&> need_double;

            std::map<std::string, char&> need_char;
            std::map<std::string, unsigned char&> need_unsigned_char;

            std::map<std::string, bool&> need_bool;

            std::map<std::string, std::string&> optional_string;

            std::map<std::string, short&> optional_short;
            std::map<std::string, int&> optional_int;
            std::map<std::string, long&> optional_long;
            std::map<std::string, long long&> optional_long_long;

            std::map<std::string, unsigned short&> optional_unsigned_short;
            std::map<std::string, unsigned int&> optional_unsigned_int;
            std::map<std::string, unsigned long&> optional_unsigned_long;
            std::map<std::string, unsigned long long&> optional_unsigned_long_long;

            std::map<std::string, float&> optional_float;
            std::map<std::string, double&> optional_double;

            std::map<std::string, char&> optional_char;
            std::map<std::string, unsigned char&> optional_unsigned_char;

            std::map<std::string, bool&> optional_bool;
    };
}