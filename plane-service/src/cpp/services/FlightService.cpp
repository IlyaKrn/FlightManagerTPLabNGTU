#include "../../header/services/FlightService.h"

using namespace std;

list<FlightModel> FlightService::getAllFlights(string token)
{
    set<string> permissions;
    permissions.insert("flight-get");
    bool isAllowed = ident.authorize(permissions, token);
    if (!isAllowed)
        throw 401;
    list<FlightModel> flights = repo.getFlights();
    return flights;
}

FlightModel FlightService::getFlightById(long int id, string token)
{
    set<string> permissions;
    permissions.insert("getFlightById");
    bool isAllowed = ident.authorize(permissions, token);
    if (!isAllowed)
        throw 401;
    list<FlightModel> flights = repo.getFlights(&id);
    return flights.front();
}

bool FlightService::createFlight(FlightModel flight, string token)
{
    set<string> permissions;
    permissions.insert("flight-create");
    bool isAllowed = ident.authorize(permissions, token);
    if (!isAllowed)
        throw 401;
    bool res = repo.createFlight(flight);
    return res;
}
