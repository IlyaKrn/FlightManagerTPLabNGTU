#pragma once
#include <list>
#include <string>
#include "../models/FlightModel.h"
#include <json/single_include/nlohmann/json.hpp>

class FlightRepository
{
public:
    std::pmr::list<FlightModel> getAllFlights(std::string id);
    bool createFlight(FlightModel flight);
};
