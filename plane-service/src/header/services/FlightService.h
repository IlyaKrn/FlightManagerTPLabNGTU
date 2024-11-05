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
    std::pmr::list<FlightModel> getAllFlights();
    FlightModel getFlightById(int id);
    bool createFlight(FlightModel flight);
};