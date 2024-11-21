#pragma once
#include <list>
#include <set>
#include <string>
#include "../repos/AirportRepository.h"
#include "../repos/FlightRepository.h"
#include "../repos/IdentityRepository.h"
#include "../repos/PlaneRepository.h"

class FlightService
{
    FlightRepository repo;
    IdentityRepository ident;
    PlaneRepository planeRepo;
    AirportRepository airportRepo;
public:
    std::list<FlightModel> getAllFlights(std::string token);
    bool createFlight(FlightModel flight, std::string token);
};