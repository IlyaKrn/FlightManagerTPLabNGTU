#include "../../header/services/AirportService.h"
#include "../../header/services/FlightService.h"
#include <ctime>
using namespace std;
bool AirportSortByTime(FlightModel a, FlightModel b)
{
    return a.getTimestampEnd() > b.getTimestampEnd();
}
list<AirportModel> AirportService::getAllAirports(string token)
{
    set<string> permissions;
    permissions.insert("airport-get");
    if (!ident.authorize(permissions, token))
        throw 401;
    list<AirportModel> airports = repo.getAirports();
    return airports;
}

AirportModel AirportService::createAirport(AirportModel airport, string token)
{
    set<string> permissions;
    permissions.insert("airport-create");
    if (!ident.authorize(permissions, token))
        throw 401;
    AirportModel res = repo.createAirport(airport);
    return res;
}

AirportModel AirportService::updateAirport(AirportModel airport, set<string> update, string token)
{
    set<string> permissions;
    permissions.insert("airport-update");
    if (!ident.authorize(permissions, token))
         throw 401;
    AirportModel res = repo.updateAirport(airport, update);
    return res;
}

bool AirportService::deleteAirport(long int id, string token)
{
    set<string> permissions;
    permissions.insert("airport-delete");
    if (!ident.authorize(permissions, token))
        throw 401;
    list<FlightModel> flights = flight.getFlights(nullptr, nullptr, nullptr, nullptr, nullptr, &id);
    flights.sort(AirportSortByTime);
    for (auto fly : flights)
    {
        if (fly.getTimestampEnd() > timer.getAddedTime() + static_cast<long int>(time(nullptr)))
            throw 409;
        long int planeId = fly.getPlaneId();
        list<FlightModel> n_flights = flight.getFlights(nullptr, nullptr, nullptr, nullptr, &planeId, &id);
        n_flights.sort(AirportSortByTime);
        if (n_flights.front().getAirportId() == id)
            throw 409;
    }
    bool res = repo.deleteAirport(id);
    return res;
}
