#include <output/info.hpp>

cookie::output::Info& cookie::output::Info::operator<<(const std::string& message) {
    std::cout << "[INFO]  | " << message << std::endl;
    return *this;
}

cookie::output::Info& cookie::output::Info::operator<<(const char* message) {
    std::cout << "[INFO]  | " << message << std::endl;
    return *this;
}

cookie::output::Info& cookie::output::Info::operator<<(std::ostream&(*manipulator)(std::ostream&)) {
    manipulator(std::cout);
    return *this;
}