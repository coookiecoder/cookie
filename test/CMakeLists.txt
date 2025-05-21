add_executable(test_string string.cpp)

target_link_libraries(test_string PRIVATE cookie)

add_test(NAME test_string COMMAND test_string)