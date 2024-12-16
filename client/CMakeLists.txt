cmake_minimum_required(VERSION 3.5)
project(plain-service)

include_directories(${CMAKE_BINARY_DIR}/libs)
enable_testing()

add_subdirectory(src src )
add_subdirectory (test test)
