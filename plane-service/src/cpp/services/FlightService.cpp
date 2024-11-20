#include "../../header/services/FlightService.h"

using namespace std;

list<FlightModel> FlightService::getAllFlights(string token)
{
    set<string> permissions;
    permissions.insert("getAllFlights");
    bool isAllowed = ident.authorize(permissions, token);
    if (!isAllowed)
        throw 401;
    list<FlightModel> flights = repo.getFlights();
    return flights;
}


bool FlightService::createFlight(FlightModel flight, string token)
{
    set<string> permissions;
    permissions.insert("createFlight");
    bool isAllowed = ident.authorize(permissions, token);
    if (!isAllowed)
        throw 401;

    bool res = repo.createFlight(flight);
    return res;
}
