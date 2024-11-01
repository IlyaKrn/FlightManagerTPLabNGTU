#pragma once
#include <list>
#include <string>
#include "../models/PlaneModel.h"

class PlaneRepository
{
public:
    std::pmr::list<std::string> getPlanes();
    bool createPlane(PlaneModel plane);
    bool deletePlane(int id);
    bool updatePlane(PlaneModel plane);
};