#pragma once
#include <string>
#include <list>
#include "../repos/AirportRepository.h"
class AirportService
{
private:
    AirportRepository repo;
public:
    std::pmr::list<std::string> getAllAirports();
    std::string getAirportById(int id);
    bool editAirport(AirportModel airport);
    bool createAirport(AirportModel airport);
    bool deleteAirport(AirportModel airport);
};
