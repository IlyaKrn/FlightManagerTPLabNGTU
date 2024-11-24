#pragma once
#include <list>
#include <set>
#include <string>
#include "../models/AirportModel.h"


class AirportRepository {
public:
    std::list<AirportModel> getAllAirports(std::string token);
    bool createAirport(AirportModel airport, std::string token);
    bool deleteAirport(long int id, std::string token);
    bool updateAirport(AirportModel airport, std::set<std::string> update, std::string token);
};
