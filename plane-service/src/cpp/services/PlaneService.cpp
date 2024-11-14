#include "../../header/services/PlaneService.h"
#include <stdexcept>

std::pmr::list<PlaneModel> PlaneService::getAllPlanes(std::string token, std::set<std::string> permissions)
{
    bool isAllowed = ident.authorize(permissions ,token);
    if (!isAllowed)
    {
        throw std::runtime_error("Отказано в доступе");
    }
    std::pmr::list<PlaneModel> planes = repo.getPlanes("");
    if (!planes.empty())
    {
        return planes;
    }
    return std::pmr::list<PlaneModel>();
}
PlaneModel PlaneService::getPlaneById(int id, std::string token, std::set<std::string> permissions)
{
    bool isAllowed = ident.authorize(permissions ,token);
    if (!isAllowed)
    {
        throw std::runtime_error("Отказано в доступе");
    }
    std::pmr::list<PlaneModel> planes = repo.getPlanes(std::to_string(id));
    PlaneModel empty_plane;
    for (auto plane : planes)
    {
        if (plane.getId() != empty_plane.getId())
        {
            return plane;
        }
    }
    return empty_plane;
}
bool PlaneService::createPlane(PlaneModel plane, std::string token, std::set<std::string> permissions)
{
    bool isAllowed = ident.authorize(permissions ,token);
    if (!isAllowed)
    {
        throw std::runtime_error("Отказано в доступе");
    }
    bool res = repo.createPlane(plane);
    if (res)
    {
        return true;
    }
    return false;
}
bool PlaneService::deletePlane(int id, std::string token, std::set<std::string> permissions)
{
    bool isAllowed = ident.authorize(permissions ,token);
    if (!isAllowed)
    {
        throw std::runtime_error("Отказано в доступе");
    }
    bool res = repo.deletePlane(id);
    if (res)
    {
        return true;
    }
    return false;
}
bool PlaneService::updatePlane(PlaneModel plane, std::string update, std::string token, std::set<std::string> permissions)
{
    bool isAllowed = ident.authorize(permissions ,token);
    if (!isAllowed)
    {
        throw std::runtime_error("Отказано в доступе");
    }
    PlaneModel n_plane = getPlaneById(plane.getId(), token, permissions);
    if (update.find("name") != std::string::npos)
    {
        n_plane.setName(plane.getName());
    }
    if (update.find("pilot") != std::string::npos)
    {
        n_plane.setPilot(plane.getPilot());
    }
    if (update.find("builtYear") != std::string::npos)
    {
        n_plane.setBuiltYear(plane.getBuiltYear());
    }
    if (update.find("brokenPercentage") != std::string::npos)
    {
        n_plane.setBrokenPercentage(plane.getBrokenPercentage());
    }
    if (update.find("speed") != std::string::npos)
    {
        n_plane.setSpeed(plane.getSpeed());
    }
    if (update.find("minAirportSize") != std::string::npos)
    {
        n_plane.setMinAirportSize(plane.getMinAirportSize());
    }
    bool res = repo.updatePlane(n_plane, update);
    if (res)
    {
        return true;
    }
    return false;
}
