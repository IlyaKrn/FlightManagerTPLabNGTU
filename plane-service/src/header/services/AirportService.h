#pragma once
#include <string>
#include <list>
#include "../repos/AirportRepository.h"
class AirportService
{
private:
    AirportRepository repo;
public:
    std::pmr::list<AirportModel> getAllAirports();
    AirportModel getAirportById(int id);
    bool editAirport(AirportModel airport, std::string update);
    bool createAirport(AirportModel airport);
    bool deleteAirport(int id);
};
