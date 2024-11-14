#pragma once
#include <list>
#include <set>
#include <string>
#include "../models/AirportModel.h"


class AirportRepository {
public:
    std::list<AirportModel> getAirports(long int* id = nullptr, std::string* name = nullptr, int* size = nullptr, double* x = nullptr, double* y = nullptr);
    bool createAirport(AirportModel airport);
    bool deleteAirport(long int id);
    bool updateAirport(AirportModel airport, std::set<std::string> update);
};
