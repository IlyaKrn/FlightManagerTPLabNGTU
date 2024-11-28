#include "../../header/services/FlightService.h"
#include <cmath>
#include <ctime>

using namespace std;
bool flightSortByTime(FlightModel a, FlightModel b)
{
    return a.getTimestampEnd() > b.getTimestampEnd();
}

list<FlightModel> FlightService::getAllFlights(string token)
{
    set<string> permissions;
    permissions.insert("flight-get");
    if (!ident.authorize(permissions, token))
         throw 401;
    list<FlightModel> flights = repo.getFlights();
    return flights;
}


bool FlightService::createFlight(FlightModel flight, string token)
{
    set<string> permissions;
    permissions.insert("flight-create");
    if (!ident.authorize(permissions, token))
         throw 401;
    long int planeId = flight.getPlaneId();
    long int airId = flight.getAirportId();
    list<PlaneModel> planes = planeRepo.getPlanes(&planeId);
    if (planes.empty())
        throw 404;
    list<AirportModel> airports = airportRepo.getAirports(&airId);
    if (airports.empty())
        throw 404;
    double x1 = airports.front().getX();
    double y1 = airports.front().getY();
    list<FlightModel> flights = repo.getFlights(nullptr, nullptr, nullptr, nullptr, &planeId);
    list<AirportModel> airports2;
    if (flights.empty())
        airports2 = airportRepo.getAirports();
    else {
        flights.sort(flightSortByTime);
        if (flights.front().getTimestampEnd() > static_cast<long int>(time(nullptr)) + timer.getAddedTime())
            throw 409;
        long int air2Id = flights.front().getAirportId();
        airports2 = airportRepo.getAirports(&air2Id);
    }
    if (airports2.empty())
        throw 404;
    int speed = planes.front().getSpeed();
    double x2 = airports2.front().getX();
    double y2 = airports2.front().getY();
    long int length = lround(sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
    long int flightTime = length/speed;
    long int timestampEnd = flight.getTimestampStart() + flightTime;
    flight.setTimestampEnd(timestampEnd);
    bool res = repo.createFlight(flight);
    return res;
}
