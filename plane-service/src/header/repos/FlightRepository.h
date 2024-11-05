#pragma once
#include <list>
#include <string>
#include "../models/FlightModel.h"
class FlightRepository
{
public:
    std::pmr::list<std::string> getAllFlights();
    bool createFlight(FlightModel flight);
};
