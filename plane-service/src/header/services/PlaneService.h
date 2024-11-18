#pragma once
#include <list>
#include <set>
#include <string>
#include "../models/PlaneModelResponse.h"
#include "../repos/PlaneRepository.h"
#include "../repos/IdentityRepository.h"

class PlaneService
{
    PlaneRepository repo;
    IdentityRepository ident;
public:
    std::list<PlaneModelResponse> getAllPlanes(std::string token);
    PlaneModelResponse getPlaneById(long int id, std::string token);
    bool createPlane(PlaneModel plane, std::string token);
    bool deletePlane(long int id, std::string token);
    bool updatePlane(PlaneModel plane, std::set<std::string> update, std::string token);
    PlaneModelResponse getPlaneCoordinates(PlaneModelResponse plane, std::string token);
};
