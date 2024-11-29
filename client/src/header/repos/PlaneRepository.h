#pragma once
#include <list>
#include <set>
#include <string>
#include "../models/PlaneModel.h"
#include "../models/PlaneModelResponse.h"

class PlaneRepository
{
public:
    std::list<PlaneModelResponse> getPlanes(std::string token);
    bool createPlane(PlaneModel plane, std::string token);
    bool deletePlane(long int id, std::string token);
    bool updatePlane(PlaneModel plane, std::set<std::string> update, std::string token);


};
