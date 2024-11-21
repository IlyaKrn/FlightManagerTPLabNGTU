#pragma once
#include <list>
#include <set>
#include <string>
#include "../models/FlightModel.h"

class FlightRepository
{
public:
    std::list<FlightModel> getAllFlights(std::string token);

    bool createFlight(FlightModel flight, std::string token);
};
