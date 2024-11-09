#pragma once
#include <list>
#include <string>
#include "../repos/FlightRepository.h"
#include "../repos/IdentityRepository.h"
class FlightService
{
private:
    FlightRepository repo;
    IdentityRepository ident;
public:
    std::pmr::list<FlightModel> getAllFlights(std::string token, std::set<std::string> permissions);
    FlightModel getFlightById(int id, std::string token, std::set<std::string> permissions);
    bool createFlight(FlightModel flight, std::string token, std::set<std::string> permissions);
};