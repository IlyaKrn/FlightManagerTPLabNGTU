#include "../../header/services/FlightService.h"

std::pmr::list<FlightModel> FlightService::getAllFlights()
{
    std::pmr::list<FlightModel> flights = repo.getFlights("");
    if (!flights.empty())
    {
        return flights;
    }
    return std::pmr::list<FlightModel>();
}

FlightModel FlightService::getFlightById(int id)
{
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
bool FlightService::createFlight(FlightModel flight)
{
    bool res = repo.createFlight(flight);
    if (res)
    {
        return true;
    }
    return false;
}


