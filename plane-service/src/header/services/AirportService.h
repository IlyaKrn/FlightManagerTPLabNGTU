#pragma once
#include <list>
#include <set>
#include <string>
#include "../repos/AirportRepository.h"
#include "../../header/repos/IdentityRepository.h"
#include "../../header/services/FlightService.h"
#include "../../header/services/PlaneService.h"
#include "../../header/services/TimeService.h"

class AirportService
{
    AirportRepository repo;
    IdentityRepository ident;
    FlightService flight;
    PlaneService plane;
    TimeService timer;
public:
    std::list<AirportModel> getAllAirports(std::string token);
    AirportModel getAirportById(long int id, std::string token);
    bool updateAirport(AirportModel airport, std::set<std::string> update, std::string token);
    bool createAirport(AirportModel airport, std::string token);
    bool deleteAirport(long int id, std::string token);
};
