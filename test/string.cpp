#include "../include/string.hpp"

int main() {
    cookie::string hello("hello");
    cookie::string world("world");

    cookie::string buffer;

    buffer = hello + world;

    if (buffer != "helloworld")
        return 1;
    buffer = (hello, world);
    if (buffer != "hello world")
        return 1;

    if (hello == world)
        return 1;

    hello += world;
    world += world;

    if (hello != "helloworld")
        return 1;

    if (world != "worldworld")
        return 1;

    return 0;
}