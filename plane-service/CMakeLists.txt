cmake_minimum_required(VERSION 3.5)
project(plain-service)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libs)
execute_process(
        COMMAND git clone "https://github.com/yhirose/cpp-httplib.git" cpp-httplib
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libs)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/libs)

add_executable(main main.cpp)