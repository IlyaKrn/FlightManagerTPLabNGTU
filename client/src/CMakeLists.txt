cmake_minimum_required(VERSION 3.5)
project(client)

add_library(src
        cpp/models/AirportModel.cpp
        cpp/models/DispatcherModel.cpp
        cpp/models/FlightModel.cpp
        cpp/models/PlaneModel.cpp
        cpp/models/PlaneModelResponse.cpp
        cpp/presenter/AirportPresenter.cpp
        cpp/presenter/DispatcherPresenter.cpp
        cpp/presenter/FlightPresenter.cpp
        cpp/presenter/IdentityPresenter.cpp
        cpp/presenter/PlanePresenter.cpp
        cpp/presenter/TimePresenter.cpp
        cpp/repos/AirportRepository.cpp
        cpp/repos/DispatcherRepository.cpp
        cpp/repos/FlightRepository.cpp
        cpp/repos/IdentityRepository.cpp
        cpp/repos/PlaneRepository.cpp
        cpp/repos/TimeRepository.cpp
        cpp/repos/TokenRepository.cpp
        header/models/AirportModel.h
        header/models/DispatcherModel.h
        header/models/FlightModel.h
        header/models/PlaneModel.h
        header/models/PlaneModelResponse.h
        header/models/RoleModel.h
        header/presentation/AirportPresenter.h
        header/presentation/DispatcherPresenter.h
        header/presentation/FlightPresenter.h
        header/presentation/IdentityPresenter.h
        header/presentation/IPresenter.h
        header/presentation/PlanePresenter.h
        header/presentation/TimePresenter.h
        header/repos/AirportRepository.h
        header/repos/DispatcherRepository.h
        header/repos/FlightRepository.h
        header/repos/IdentityRepository.h
        header/repos/PlaneRepository.h
        header/repos/TimeRepository.h
        header/repos/TokenRepository.h
        Config.h
)

target_link_libraries(src nlohmann_json httplib)

add_executable(client main.cpp)

target_link_libraries(client src)

if(WIN32)
    target_link_libraries(client wsock32 ws2_32)
endif()