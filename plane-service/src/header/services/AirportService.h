#pragma once
#include <list>
#include <set>
#include <string>
#include "../repos/AirportRepository.h"
#include "../../header/repos/IdentityRepository.h"
#include "../../header/repos/FlightRepository.h"
#include "../../header/services/TimeService.h"

class AirportService
{
    AirportRepository repo;
    IdentityRepository ident;
    FlightRepository flight;
    TimeRepository timer;
public:
    std::list<AirportModel> getAllAirports(std::string token);
    bool updateAirport(AirportModel airport, std::set<std::string> update, std::string token);
    bool createAirport(AirportModel airport, std::string token);
    bool deleteAirport(long int id, std::string token);
};
