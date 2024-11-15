#pragma once
#include <list>
#include <set>
#include <string>
#include "../repos/PlaneRepository.h"
#include "../repos/IdentityRepository.h"

class PlaneService
{
    PlaneRepository repo;
    IdentityRepository ident;
public:
    std::list<PlaneModel> getAllPlanes(std::string token, std::set<std::string> permissions);
    PlaneModel getPlaneById(long int id, std::string token, std::set<std::string> permissions);
    bool createPlane(PlaneModel plane, std::string token, std::set<std::string> permissions);
    bool deletePlane(long int id, std::string token, std::set<std::string> permissions);
    bool updatePlane(PlaneModel plane, std::set<std::string> update, std::string token, std::set<std::string> permissions);

};
