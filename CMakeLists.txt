cmake_minimum_required(VERSION 3.28)
project(cookie)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

include_directories(include)

add_library(cookie_string OBJECT
		source/string.cpp
		include/string.hpp
)

add_library(cookie_matrix OBJECT
		source/matrix.cpp
		source/matrix/matrix2D.cpp
		source/matrix/matrix3D.cpp
		source/matrix/matrix4D.cpp
		include/matrix.hpp
		include/matrix/matrix2D.hpp
		include/matrix/matrix3D.hpp
		include/matrix/matrix4D.hpp
)

add_library(cookie_container OBJECT
		source/container/list.cpp
		source/container/node.cpp
		source/container/array.cpp
		include/container/list.hpp
		include/container/node.hpp
		include/container/array.hpp
)

add_library(cookie STATIC
		$<TARGET_OBJECTS:cookie_string>
		$<TARGET_OBJECTS:cookie_matrix>
		$<TARGET_OBJECTS:cookie_container>
)

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp)
	add_executable(test test/main.cpp)
	target_link_libraries(test cookie)
endif ()