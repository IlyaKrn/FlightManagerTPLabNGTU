#pragma once
#include <list>
#include <string>
#include "../models/AirportModel.h"
#include <json/single_include/nlohmann/json.hpp>


class AirportRepository {
public:
    std::pmr::list<AirportModel> getAirports(std::string id);
    bool createAirport(AirportModel airport);
    bool deleteAirport(int id);
    bool updateAirport(AirportModel airport, std::string update);
};
