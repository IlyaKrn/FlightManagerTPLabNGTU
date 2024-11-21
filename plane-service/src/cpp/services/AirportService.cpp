#include "../../header/services/AirportService.h"

using namespace std;

list<AirportModel> AirportService::getAllAirports(string token)
{
    set<string> permissions;
    permissions.insert("airport-get");
    bool isAllowed = ident.authorize(permissions, token);
    if (!isAllowed)
        throw 401;
    list<AirportModel> airports = repo.getAirports();
    return airports;
}

AirportModel AirportService::getAirportById(long int id, string token)
{
    set<string> permissions;
    permissions.insert("getAirportById");
    bool isAllowed = ident.authorize(permissions, token);
    if (!isAllowed)
        throw 401;
    list<AirportModel> airports = repo.getAirports(&id);
    return airports.front();
}

bool AirportService::createAirport(AirportModel airport, string token)
{
    set<string> permissions;
    permissions.insert("airport-create");
    bool isAllowed = ident.authorize(permissions, token);
    if (!isAllowed)
        throw 401;
    bool res = repo.createAirport(airport);
    return res;
}

bool AirportService::updateAirport(AirportModel airport, set<string> update, string token)
{
    set<string> permissions;
    permissions.insert("airport-update");
    bool isAllowed = ident.authorize(permissions, token);
    if (!isAllowed)
        throw 401;
    AirportModel n_airport = getAirportById(airport.getId(), token);
    if (update.count("name") > 0)
        n_airport.setName(airport.getName());
    if (update.count("size") > 0)
        n_airport.setSize(airport.getSize());
    if (update.count("x") > 0)
        n_airport.setX(airport.getX());
    if (update.count("y") > 0)
        n_airport.setY(airport.getY());
    bool res = repo.updateAirport(n_airport, update);
    return res;
}

bool AirportService::deleteAirport(long int id, string token)
{
    set<string> permissions;
    permissions.insert("airport-delete");
    bool isAllowed = ident.authorize(permissions, token);
    if (!isAllowed)
        throw 401;
    list<FlightModel> flights = flight.getAllFlights(token);
    for (auto fly : flights)
    {
        if (fly.getAirportId() == id)
        {
            if (fly.getTimestampEnd() >= timer.getCurrentTime(token))
                throw 409;
        }
    }
    bool res = repo.deleteAirport(id);
    return res;
}
