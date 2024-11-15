#pragma once
#include <list>
#include <set>
#include <string>
#include "../models/AirportModel.h"


class AirportRepository {
public:

  //methods with requests to plane-service and identity-service (not in one class)
    std::list<AirportModel> getAirports(std::string token);
    bool createAirport(AirportModel airport, std::string token);
    bool deleteAirport(long int id, std::string token);
    bool updateAirport(AirportModel airport, std::set<std::string> update, std::string token);
};
