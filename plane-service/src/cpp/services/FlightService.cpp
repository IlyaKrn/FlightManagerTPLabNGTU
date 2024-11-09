#include "../../header/services/FlightService.h"
#include <stdexcept>

std::pmr::list<FlightModel> FlightService::getAllFlights(std::string token, std::set<std::string> permissions)
{
    bool isAllowed = ident.authorize(permissions ,token);
    if (!isAllowed)
    {
        throw std::runtime_error("Отказано в доступе");
    }
    std::pmr::list<FlightModel> flights = repo.getFlights("");
    if (!flights.empty())
    {
        return flights;
    }
    return std::pmr::list<FlightModel>();
}

FlightModel FlightService::getFlightById(int id, std::string token, std::set<std::string> permissions)
{
    bool isAllowed = ident.authorize(permissions ,token);
    if (!isAllowed)
    {
        throw std::runtime_error("Отказано в доступе");
    }
    std::pmr::list<FlightModel> flights = repo.getFlights(std::to_string(id));
    FlightModel empty_flight;
    for (auto flight : flights)
    {
        if (flight.getId() != empty_flight.getId())
        {
            return flight;
        }
    }
    return empty_flight;
}
bool FlightService::createFlight(FlightModel flight, std::string token, std::set<std::string> permissions)
{
    bool isAllowed = ident.authorize(permissions ,token);
    if (!isAllowed)
    {
        throw std::runtime_error("Отказано в доступе");
    }
    bool res = repo.createFlight(flight);
    if (res)
    {
        return true;
    }
    return false;
}


