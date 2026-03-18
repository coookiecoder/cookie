#include <output/error.hpp>

cookie::output::Error& cookie::output::Error::operator<<(const std::string& message) {
    std::cout << "[ERROR] | " << message << std::endl;
    return *this;
}

cookie::output::Error& cookie::output::Error::operator<<(const char* message) {
    std::cout << "[ERROR] | " << message << std::endl;
    return *this;
}

cookie::output::Error& cookie::output::Error::operator<<(std::ostream&(*manipulator)(std::ostream&)) {
    manipulator(std::cout);
    return *this;
}