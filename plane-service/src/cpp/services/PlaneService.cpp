#include "../../header/services/PlaneService.h"
#include <algorithm>
#include "../../header/models/PlaneModelResponse.h"
#include <cmath>
#include <ctime>

bool PlaneSortByTime(FlightModel a, FlightModel b)
{
    return a.getTimestampEnd() >
    b.getTimestampEnd();
}
using namespace std;
list<PlaneModelResponse> PlaneService::getAllPlanes(string token)
{
    set<string> permissions;
    permissions.insert("plane-get");
    if (!ident.authorize(permissions, token))
         throw 401;
    list<PlaneModel> planes = repo.getPlanes();
    list<PlaneModelResponse> planesResponse;
    for (auto plane : planes)
    {
        //create object planeResponse
        PlaneModelResponse planeResponse(planes.front().getId(), planes.front().getName(), planes.front().getPilot(), planes.front().getBuiltYear(), planes.front().getBrokenPercentage(), planes.front().getSpeed(), planes.front().getMinAirportSize(), 0, 0);
        long int planeId = planes.front().getId();
        int speed = plane.getSpeed();
        //Taking all flights with our plane
        list<FlightModel> flights = flight.getFlights(nullptr, nullptr, nullptr, nullptr,&planeId);
        if (!flights.empty())
        {
            //If we found flights, we search last flight and, if that's it, current flight
            flights.sort(PlaneSortByTime);
            bool have_last_flight = true;
            bool have_current_flight = true;
            if (flights.front().getTimestampEnd() > static_cast<long int>(time(nullptr)) + timer.getAddedTime()) {
                if (flights.size() < 2)
                    have_last_flight = false;
            } else
                have_current_flight = false;
            double x1;
            double y1;
            if (have_last_flight) //if our plane have last flight, we are looking for airport from this flight
            {
                //Found airport from what plane took off
                auto it = flights.begin();
                if (have_current_flight)
                    it++;
                FlightModel last_flight = *it;
                long int last_flight_air_id = last_flight.getAirportId();
                list<AirportModel> airport1 = air.getAirports(&last_flight_air_id);
                if (airport1.empty())
                    throw 404;
                x1 = airport1.front().getX(); //start airport coordinate x
                y1 = airport1.front().getY(); //start airport coordinate y
            } else { //if we didn't find last flight we take first airport from list of airports
                list<AirportModel> airport1 = air.getAirports();
                if (airport1.empty())
                    throw 404;
                x1 = airport1.front().getX(); //start airport coordinate x
                y1 = airport1.front().getY(); //start airport coordinate y
            }
            if (have_current_flight)
            {
                FlightModel current_flight = flights.front();
                //If we found current flight, we will find airport from that flight
                long int current_flight_air_id = current_flight.getAirportId();
                list<AirportModel> airport2 = air.getAirports(&current_flight_air_id);
                if (airport2.empty())
                    throw 404;
                double x2 = airport2.front().getX(); //end airport coordnate x
                double y2 = airport2.front().getY(); //end airport coordinate y
                double length = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)); //length of flight
                long int elapsedTime = timer.getAddedTime() + static_cast<long int>(time(nullptr)) - current_flight.getTimestampStart();
                //Calculating airport coordinates
                double newX = x1 + (x2 - x1) * (speed * elapsedTime / length);
                double newY = y1 + (y2 - y1) * (speed * elapsedTime / length);
                planeResponse.setX(newX);
                planeResponse.setY(newY);
            } else
            {
                //If we didn't find executing flight, we set coordinates of start airport
                planeResponse.setX(x1);
                planeResponse.setY(y1);
            }

        } else
        {
            //If plane didn't fly yet, we take coordinates of airport, that first in list of airports.
            list<AirportModel> airports = air.getAirports();
            if (airports.empty())
                throw 404;
            planeResponse.setX(airports.front().getX());
            planeResponse.setY(airports.front().getY());
        }
        planesResponse.push_back(planeResponse);
    }
    return planesResponse;
}

bool PlaneService::createPlane(PlaneModel plane, string token)
{
    set<string> permissions;
    permissions.insert("plane-create");
    if (!ident.authorize(permissions, token))
         throw 401;
    bool res = repo.createPlane(plane);
    return res;
}
bool PlaneService::deletePlane(long int id, string token)
{
    set<string> permissions;
    permissions.insert("plane-delete");
    if (!ident.authorize(permissions, token))
         throw 401;
    list<FlightModel> flights = flight.getFlights(nullptr, nullptr, nullptr, nullptr, &id);
    flights.sort(PlaneSortByTime);
    if (flights.front().getTimestampEnd() > timer.getAddedTime())
        throw 409;
    bool res = repo.deletePlane(id);
    return res;
}
bool PlaneService::updatePlane(PlaneModel plane, set<string> update, string token)
{
    set<string> permissions;
    permissions.insert("plane-update");
    if (!ident.authorize(permissions, token))
         throw 401;
    long int planeId = plane.getId();
    list<PlaneModel> n_planes = repo.getPlanes(&planeId);
    PlaneModel n_plane = n_planes.front();
    if (update.count("name") > 0)
        n_plane.setName(plane.getName());
    if (update.count("pilot") > 0)
        n_plane.setPilot(plane.getPilot());
    if (update.count("builtYear") > 0)
        n_plane.setBuiltYear(plane.getBuiltYear());
    if (update.count("brokenPercentage") > 0)
        n_plane.setBrokenPercentage(plane.getBrokenPercentage());
    if (update.count("speed") > 0)
        n_plane.setSpeed(plane.getSpeed());
    if (update.count("minAirportSize") > 0)
        n_plane.setMinAirportSize(plane.getMinAirportSize());
    bool res = repo.updatePlane(n_plane, update);
    return res;
}

