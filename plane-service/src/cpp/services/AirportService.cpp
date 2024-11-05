#include "../../header/services/AirportService.h"

std::pmr::list<AirportModel> AirportService::getAllAirports()
{
    std::pmr::list<AirportModel> airports = repo.getAirports("");
    if (!airports.empty())
    {
        return airports;
    }
    return std::pmr::list<AirportModel>();
}

AirportModel AirportService::getAirportById(int id)
{
    std::pmr::list<AirportModel> airports = repo.getAirports(std::to_string(id));
    AirportModel empty_airport;
    for (auto airport : airports)
    {
        if (airport.getId() != empty_airport.getId())
        {
            return airport;
        }
    }
    return empty_airport;
}

bool AirportService::createAirport(AirportModel airport)
{
    bool res = repo.createAirport(airport);
    if (res)
    {
        return true;
    }
    return false;
}
bool AirportService::editAirport(AirportModel airport, std::string update)
{
    AirportModel n_airport = getAirportById(airport.getId());
    if (update.find("name") != std::string::npos)
    {
        n_airport.setName(airport.getName());
    }
    if (update.find("size") != std::string::npos)
    {
        n_airport.setSize(airport.getSize());
    }
    if (update.find("x") != std::string::npos)
    {
        n_airport.setX(airport.getX());
    }
    if (update.find("y") != std::string::npos)
    {
        n_airport.setY(airport.getY());
    }
    bool res = repo.updateAirport(n_airport, update);
    if (res)
    {
        return true;
    }
    return false;
}
bool AirportService::deleteAirport(int id)
{
    bool res = repo.deleteAirport(id);
    if (res)
    {
        return true;
    }
    return false;
}