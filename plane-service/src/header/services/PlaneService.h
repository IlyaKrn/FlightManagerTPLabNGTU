#pragma once
#include <list>
#include <string>
#include "../repos/PlaneRepository.h"
#include "../repos/IdentityRepository.h"


class PlaneService
{
private:
    PlaneRepository repo;
    IdentityRepository ident;
public:
    std::pmr::list<PlaneModel> getAllPlanes(std::string token, std::set<std::string> permissions);
    PlaneModel getPlaneById(int id, std::string token, std::set<std::string> permissions);
    bool createPlane(PlaneModel plane, std::string token, std::set<std::string> permissions);
    bool deletePlane(int id, std::string token, std::set<std::string> permissions);
    bool updatePlane(PlaneModel plane, std::string update, std::string token, std::set<std::string> permissions);

};
