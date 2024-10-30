cmake_minimum_required(VERSION 3.5)
project(plain-service)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libs)
execute_process(
        COMMAND git clone "https://github.com/yhirose/cpp-httplib.git" cpp-httplib
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libs)
execute_process(
        COMMAND git clone "https://github.com/nlohmann/json.git" json
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libs)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/libs)

add_executable(main src/main.cpp
        src/cpp/controllers/IController.cpp
        src/header/controllers/IController.h
        src/cpp/controllers/AirportController.cpp
        src/header/controllers/AirportController.h
        src/header/Config.h
        src/cpp/repos/AirportRepository.cpp
        src/header/repos/AirportRepository.h
)
if(WIN32)
    target_link_libraries(main wsock32 ws2_32)
endif()