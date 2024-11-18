#pragma once
#include <list>
#include <set>
#include <string>
#include "../repos/FlightRepository.h"
#include "../repos/IdentityRepository.h"

class FlightService
{
    FlightRepository repo;
    IdentityRepository ident;
public:
    std::list<FlightModel> getAllFlights(std::string token);
    FlightModel getFlightById(long int id, std::string token);
    bool createFlight(FlightModel flight, std::string token);
};