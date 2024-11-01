#pragma once
#include "../repos/PlaneRepository.h"
#include <list>
#include <string>

class PlaneService
{
private:
    PlaneRepository repo;
public:
    std::pmr::list<std::string> getAllPlanes();
    std::string getPlaneById(int id);
    bool createPlane(PlaneModel plane);
    bool deletePlane(int id);
    bool updatePlane(PlaneModel plane);

};
