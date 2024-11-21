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
    permissions.insert("getAllAirports");
    // bool isAllowed = ident.authorize(permissions, token);
    // if (!isAllowed)
    //     throw 401;
    list<AirportModel> airports = repo.getAirports();
    return airports;
}


bool AirportService::createAirport(AirportModel airport, string token)
{
    set<string> permissions;
    permissions.insert("createAirport");
    // bool isAllowed = ident.authorize(permissions, token);
    // if (!isAllowed)
    //     throw 401;
    bool res = repo.createAirport(airport);
    return res;
}

bool AirportService::updateAirport(AirportModel airport, set<string> update, string token)
{
    set<string> permissions;
    permissions.insert("updateAirport");
    // bool isAllowed = ident.authorize(permissions, token);
    //  if (!isAllowed)
    //      throw 401;
    long int airId = airport.getId();
    list<AirportModel> n_airports = repo.getAirports(&airId);
    AirportModel n_airport = n_airports.front();
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
    permissions.insert("deleteAirport");
    // bool isAllowed = ident.authorize(permissions, token);
    // if (!isAllowed)
    //     throw 401;
    list<FlightModel> flights = flight.getFlights(nullptr, nullptr, nullptr, nullptr, nullptr, &id);
    flights.sort(AirportSortByTime);
    if (flights.front().getTimestampEnd() > timer.getAddedTime())
        throw 409;
    long int planeId = flights.front().getPlaneId();
    list<FlightModel> n_flights = flight.getFlights(nullptr, nullptr, nullptr, nullptr, &planeId, nullptr);
    n_flights.sort(AirportSortByTime);
    if (flights.front().getAirportId() == id)
        throw 409;
    bool res = repo.deleteAirport(id);
    return res;
}
