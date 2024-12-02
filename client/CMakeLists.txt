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
        src/cpp/models/AirportModel.cpp
        src/cpp/models/DispatcherModel.cpp
        src/cpp/models/FlightModel.cpp
        src/cpp/models/PlaneModel.cpp
        src/cpp/models/PlaneModelResponse.cpp
        src/cpp/presenter
        src/cpp/presenter/AirportPresenter.cpp
        src/cpp/presenter/DispatcherPresenter.cpp
        src/cpp/presenter/FlightPresenter.cpp
        src/cpp/presenter/IdentityPresenter.cpp
        src/cpp/presenter/PlanePresenter.cpp
        src/cpp/presenter/TimePresenter.cpp
        src/cpp/repos
        src/cpp/repos/AirportRepository.cpp
        src/cpp/repos/DispatcherRepository.cpp
        src/cpp/repos/FlightRepository.cpp
        src/cpp/repos/IdentityRepository.cpp
        src/cpp/repos/PlaneRepository.cpp
        src/cpp/repos/TimeRepository.cpp
        src/cpp/repos/TokenRepository.cpp
        src/header
        src/header/models
        src/header/models/AirportModel.h
        src/header/models/DispatcherModel.h
        src/header/models/FlightModel.h
        src/header/models/PlaneModel.h
        src/header/models/PlaneModelResponse.h
        src/header/models/RoleModel.h
        src/header/presentation
        src/header/presentation/AirportPresenter.h
        src/header/presentation/DispatcherPresenter.h
        src/header/presentation/FlightPresenter.h
        src/header/presentation/IdentityPresenter.h
        src/header/presentation/IPresenter.h
        src/header/presentation/PlanePresenter.h
        src/header/presentation/TimePresenter.h
        src/header/repos
        src/header/repos/AirportRepository.h
        src/header/repos/DispatcherRepository.h
        src/header/repos/FlightRepository.h
        src/header/repos/IdentityRepository.h
        src/header/repos/PlaneRepository.h
        src/header/repos/TimeRepository.h
        src/header/repos/TokenRepository.h
        src/Config.h


)
if(WIN32)
    target_link_libraries(main wsock32 ws2_32)
endif()