cmake_minimum_required(VERSION 3.28)
project(cookie)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

include_directories(include)

add_library(cookie_string OBJECT
		source/string.cpp
)

add_library(cookie_matrix OBJECT
		source/matrix.cpp
)

add_library(cookie STATIC
		$<TARGET_OBJECTS:cookie_string>
		$<TARGET_OBJECTS:cookie_matrix>
)