#pragma once
#include <list>
#include <set>
#include <string>
#include "../repos/AirportRepository.h"
#include "../../header/repos/IdentityRepository.h"


class AirportService
{
    AirportRepository repo;
    IdentityRepository ident;
public:
    std::list<AirportModel> getAllAirports(std::string token, std::set<std::string> permissions);
    AirportModel getAirportById(long int id, std::string token, std::set<std::string> permissions);
    bool editAirport(AirportModel airport, std::set<std::string> update, std::string token, std::set<std::string> permissions);
    bool createAirport(AirportModel airport, std::string token, std::set<std::string> permissions);
    bool deleteAirport(long int id, std::string token, std::set<std::string> permissions);
};
