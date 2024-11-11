#pragma once
#include <list>
#include <string>
#include "../models/FlightModel.h"

class FlightRepository
{
public:
    std::list<FlightModel> getFlights(long int id, long int timestampStart, long int timestampEnd, long int dispatcherId, long int planeId, long int airportId);
    bool createFlight(FlightModel flight);
};
