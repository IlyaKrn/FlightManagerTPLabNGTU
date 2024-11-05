#pragma once
#include <list>
#include <string>
#include "../models/PlaneModel.h"
#include <json/single_include/nlohmann/json.hpp>


class PlaneRepository
{
public:
    std::pmr::list<PlaneModel> getPlanes(std::string id);
    bool createPlane(PlaneModel plane);
    bool deletePlane(int id);
    bool updatePlane(PlaneModel plane, std::string update);
};