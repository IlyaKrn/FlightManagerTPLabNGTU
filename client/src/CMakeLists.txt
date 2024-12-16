cmake_minimum_required(VERSION 3.5)
project(plain-service)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
execute_process(
        COMMAND git clone "https://github.com/yhirose/cpp-httplib.git" cpp-httplib
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
execute_process(
        COMMAND git clone "https://github.com/nlohmann/json.git" json
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/libs)

include_directories(${CMAKE_BINARY_DIR}/libs)

add_executable(main main.cpp
        cpp/models/AirportModel.cpp
        cpp/models/DispatcherModel.cpp
        cpp/models/FlightModel.cpp
        cpp/models/PlaneModel.cpp
        cpp/models/PlaneModelResponse.cpp
        cpp/presenter
        cpp/presenter/AirportPresenter.cpp
        cpp/presenter/DispatcherPresenter.cpp
        cpp/presenter/FlightPresenter.cpp
        cpp/presenter/IdentityPresenter.cpp
        cpp/presenter/PlanePresenter.cpp
        cpp/presenter/TimePresenter.cpp
        cpp/repos
        cpp/repos/AirportRepository.cpp
        cpp/repos/DispatcherRepository.cpp
        cpp/repos/FlightRepository.cpp
        cpp/repos/IdentityRepository.cpp
        cpp/repos/PlaneRepository.cpp
        cpp/repos/TimeRepository.cpp
        cpp/repos/TokenRepository.cpp
        header
        header/models
        header/models/AirportModel.h
        header/models/DispatcherModel.h
        header/models/FlightModel.h
        header/models/PlaneModel.h
        header/models/PlaneModelResponse.h
        header/models/RoleModel.h
        header/presentation
        header/presentation/AirportPresenter.h
        header/presentation/DispatcherPresenter.h
        header/presentation/FlightPresenter.h
        header/presentation/IdentityPresenter.h
        header/presentation/IPresenter.h
        header/presentation/PlanePresenter.h
        header/presentation/TimePresenter.h
        header/repos
        header/repos/AirportRepository.h
        header/repos/DispatcherRepository.h
        header/repos/FlightRepository.h
        header/repos/IdentityRepository.h
        header/repos/PlaneRepository.h
        header/repos/TimeRepository.h
        header/repos/TokenRepository.h
        Config.h


)
if(WIN32)
    target_link_libraries(main wsock32 ws2_32)
endif()