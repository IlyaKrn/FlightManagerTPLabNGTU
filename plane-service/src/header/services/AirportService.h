#pragma once
#include <string>
#include <list>
#include "../repos/AirportRepository.h"
#include "../../header/repos/IdentityRepository.h"
class AirportService
{
private:
    AirportRepository repo;
    IdentityRepository ident;
public:
    std::pmr::list<AirportModel> getAllAirports(std::string token, std::set<std::string> permissions);
    AirportModel getAirportById(int id, std::string token, std::set<std::string> permissions);
    bool editAirport(AirportModel airport, std::string update, std::string token, std::set<std::string> permissions);
    bool createAirport(AirportModel airport, std::string token, std::set<std::string> permissions);
    bool deleteAirport(int id, std::string token, std::set<std::string> permissions);
};
