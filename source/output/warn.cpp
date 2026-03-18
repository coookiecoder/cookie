#include <output/warn.hpp>

cookie::output::Warn& cookie::output::Warn::operator<<(const std::string& message) {
    std::cout << "[WARN]  | " << message << std::endl;
    return *this;
}

cookie::output::Warn& cookie::output::Warn::operator<<(const char* message) {
    std::cout << "[WARN]  | " << message << std::endl;
    return *this;
}

cookie::output::Warn& cookie::output::Warn::operator<<(std::ostream&(*manipulator)(std::ostream&)) {
    manipulator(std::cout);
    return *this;
}