#include "../../header/services/FlightService.h"

using namespace std;
list<FlightModel> FlightService::getAllFlights(string token)
{
    try {
        set<string> permissions;
        permissions.insert("getAllFlights");
        bool isAllowed = ident.authorize(permissions ,token);
        if (!isAllowed)
        {
            throw string("401");
        }
        list<FlightModel> flights = repo.getFlights();
        return flights;
    } catch (const string& e)
    {
        throw string(e);
    }
}

FlightModel FlightService::getFlightById(long int id, string token)
{
    try
    {
        set<string> permissions;
        permissions.insert("getFlightById");
        bool isAllowed = ident.authorize(permissions ,token);
        if (!isAllowed)
        {
            throw string("401");
        }
        list<FlightModel> flights = repo.getFlights(&id);
        return flights.front();
    } catch (const string& e)
    {
        throw string(e);
    }
}
bool FlightService::createFlight(FlightModel flight, string token)
{
    try
    {
        set<string> permissions;
        permissions.insert("createFlight");
        bool isAllowed = ident.authorize(permissions ,token);
        if (!isAllowed)
        {
            throw string("401");
        }
        bool res = repo.createFlight(flight);
        return res;
    } catch (const string& e)
    {
        throw string(e);
    }
}


