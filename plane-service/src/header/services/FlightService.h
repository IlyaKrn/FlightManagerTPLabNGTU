#pragma once
#include <string>
#include <list>
#include <json/single_include/nlohmann/json.hpp>

#include "../repos/FlightRepository.h"

class FlightService
{
private:
    FlightRepository repo;
public:
    std::pmr::list<std::string> getAllFlights();
    std::string getFlightById(int id);
    bool createFlight(FlightModel flight);
};