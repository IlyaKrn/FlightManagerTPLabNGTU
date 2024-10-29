#pragma once
#include <list>
#include <string>


class AirportRepository {
public:
    std::pmr::list<std::string> getAirports(int param1, std::string param2);
};
