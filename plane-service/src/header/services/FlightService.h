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
    std::list<FlightModel> getAllFlights(std::string token, std::set<std::string> permissions);
    FlightModel getFlightById(long int id, std::string token, std::set<std::string> permissions);
    bool createFlight(FlightModel flight, std::string token, std::set<std::string> permissions);
};