#pragma once
#include <list>
#include <string>
#include "../models/AirportModel.h"
#include <cpp-httplib/httplib.h>
#include <json/single_include/nlohmann/json.hpp>
#include "../../header/Config.h"

class AirportRepository {
public:
    std::pmr::list<std::string> getAirports();
    bool createAirport(AirportModel airport);
    bool deleteAirport(int id);
    bool updateAirport(AirportModel airport);
};
