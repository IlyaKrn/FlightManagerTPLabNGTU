#pragma once
#include <list>
#include <set>
#include <string>
#include "../models/PlaneModel.h"

class PlaneRepository
{
public:
    std::list<PlaneModel> getPlanes(long int id, std::string name, std::string pilot, int builtYear, int brokenPercentage, int speed, int minAirportSize);
    bool createPlane(PlaneModel plane);
    bool deletePlane(long int id);
    bool updatePlane(PlaneModel plane, std::set<std::string> update);


};