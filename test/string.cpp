#include "../source/cookie_string/string.hpp"

int main(void) {
    cookie::string hello("hello");
    cookie::string world("world");

    cookie::string buffer = hello + world;

    std::cout << buffer << std::endl;
}