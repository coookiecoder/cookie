cmake_minimum_required(VERSION 3.28)
project(cookie)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -g3)

include_directories(include)

add_library(cookie_string
        source/string.cpp)

add_library(cookie STATIC
		$<TARGET_OBJECTS:cookie_string>)

set(CMAKE_CXX_STANDARD 23)
