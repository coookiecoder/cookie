#include <parser/ArgumentParser.hpp>

void cookie::ArgumentParser::parse(const int argc, const char** argv) {
    for (int i = 1; i < argc; i++) {
        if (const auto bool_need_argument = this->need_bool.find(argv[i]); bool_need_argument != this->need_bool.end())
            bool_need_argument->second = true;
        else if (const auto bool_optional_argument = this->optional_bool.find(argv[i]); bool_optional_argument != this->optional_bool.end())
            bool_optional_argument->second = true;
        else if (i + 1 == argc)
            break;
        else if (this->parse_needed(argv[i], argv[i + 1]))
            i++;
        else if (this->parse_optional(argv[i], argv[i + 1]))
            i++;
    }
}

bool cookie::ArgumentParser::parse_needed(const std::string& current, const std::string& next) {
    if (const auto string_argument = this->need_string.find(current); string_argument != this->need_string.end())
        string_argument->second = next;


    else if (const auto short_argument = this->need_short.find(current); short_argument != this->need_short.end())
        short_argument->second = static_cast<short>(strtoll(next.c_str(), nullptr, 10));

    else if (const auto int_argument = this->need_int.find(current); int_argument != this->need_int.end())
        int_argument->second = static_cast<int>(strtoll(next.c_str(), nullptr, 10));

    else if (const auto long_argument = this->need_long.find(current); long_argument != this->need_long.end())
        long_argument->second = static_cast<long>(strtoll(next.c_str(), nullptr, 10));

    else if (const auto long_long_argument = this->need_long_long.find(current); long_long_argument != this->need_long_long.end())
        long_long_argument->second = strtoll(next.c_str(), nullptr, 10);


    else if (const auto unsigned_short_argument = this->need_unsigned_short.find(current); unsigned_short_argument != this->need_unsigned_short.end())
        unsigned_short_argument->second = static_cast<unsigned short>(strtoull(next.c_str(), nullptr, 10));

    else if (const auto unsigned_int_argument = this->need_unsigned_int.find(current); unsigned_int_argument != this->need_unsigned_int.end())
        unsigned_int_argument->second = static_cast<unsigned int>(strtoull(next.c_str(), nullptr, 10));

    else if (const auto unsigned_long_argument = this->need_unsigned_long.find(current); unsigned_long_argument != this->need_unsigned_long.end())
        unsigned_long_argument->second = static_cast<unsigned long>(strtoull(next.c_str(), nullptr, 10));

    else if (const auto unsigned_long_long_argument = this->need_unsigned_long_long.find(current); unsigned_long_long_argument != this->need_unsigned_long_long.end())
        unsigned_long_long_argument->second = strtoull(next.c_str(), nullptr, 10);


    else if (const auto float_argument = this->need_float.find(current); float_argument != this->need_float.end())
        float_argument->second = strtof(next.c_str(), nullptr);

    else if (const auto double_argument = this->need_double.find(current); double_argument != this->need_double.end())
        double_argument->second = strtod(next.c_str(), nullptr);

    else
        return false;
    return true;
}

bool cookie::ArgumentParser::parse_optional(const std::string& current, const std::string& next) {
    if (const auto string_argument = this->optional_string.find(current); string_argument != this->optional_string.end())
        string_argument->second = next;


    else if (const auto short_argument = this->optional_short.find(current); short_argument != this->optional_short.end())
        short_argument->second = static_cast<short>(strtoll(next.c_str(), nullptr, 10));

    else if (const auto int_argument = this->optional_int.find(current); int_argument != this->optional_int.end())
        int_argument->second = static_cast<int>(strtoll(next.c_str(), nullptr, 10));

    else if (const auto long_argument = this->optional_long.find(current); long_argument != this->optional_long.end())
        long_argument->second = static_cast<long>(strtoll(next.c_str(), nullptr, 10));

    else if (const auto long_long_argument = this->optional_long_long.find(current); long_long_argument != this->optional_long_long.end())
        long_long_argument->second = strtoll(next.c_str(), nullptr, 10);


    else if (const auto unsigned_short_argument = this->optional_unsigned_short.find(current); unsigned_short_argument != this->optional_unsigned_short.end())
        unsigned_short_argument->second = static_cast<unsigned short>(strtoull(next.c_str(), nullptr, 10));

    else if (const auto unsigned_int_argument = this->optional_unsigned_int.find(current); unsigned_int_argument != this->optional_unsigned_int.end())
        unsigned_int_argument->second = static_cast<unsigned int>(strtoull(next.c_str(), nullptr, 10));

    else if (const auto unsigned_long_argument = this->optional_unsigned_long.find(current); unsigned_long_argument != this->optional_unsigned_long.end())
        unsigned_long_argument->second = static_cast<unsigned long>(strtoull(next.c_str(), nullptr, 10));

    else if (const auto unsigned_long_long_argument = this->optional_unsigned_long_long.find(current); unsigned_long_long_argument != this->optional_unsigned_long_long.end())
        unsigned_long_long_argument->second = strtoull(next.c_str(), nullptr, 10);


    else if (const auto float_argument = this->optional_float.find(current); float_argument != this->optional_float.end())
        float_argument->second = strtof(next.c_str(), nullptr);

    else if (const auto double_argument = this->optional_double.find(current); double_argument != this->optional_double.end())
        double_argument->second = strtod(next.c_str(), nullptr);

    else
        return false;
    return true;
}