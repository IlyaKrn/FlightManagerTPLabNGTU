#include "../../header/services/PlaneService.h"
#include <algorithm>
#include "../../header/models/PlaneModelResponse.h"
#include <cmath>
#include <ctime>

bool sortByTime(FlightModel a, FlightModel b)
{
    return a.getTimestampEnd() > b.getTimestampEnd();
}
using namespace std;
list<PlaneModelResponse> PlaneService::getAllPlanes(string token)
{
    set<string> permissions;
    permissions.insert("getAllPlanes");
    bool isAllowed = ident.authorize(permissions ,token);
    if (!isAllowed)
        throw 401;
    list<PlaneModel> planes = repo.getPlanes();
    list<PlaneModelResponse> planesResponse;
    for (auto plane : planes)
    {
        //create object planeResponse
        PlaneModelResponse planeResponse(planes.front().getId(), planes.front().getName(), planes.front().getPilot(), planes.front().getBuiltYear(), planes.front().getBrokenPercentage(), planes.front().getSpeed(), planes.front().getMinAirportSize(), 0, 0);
        long int planeId = planes.front().getId();
        //Taking all flights with our plane
        list<FlightModel> flights = flight.getFlights(nullptr, nullptr, nullptr, nullptr,&planeId);
        if (!flights.empty())
        {
            //If we found flights, we search last flight and, if that's it, current flight
            long int last_flight_time = 0; //in there we will have last flight time
            FlightModel last_flight(0,0,0,0,0,0);
            FlightModel current_fly(0,0,0,0,0,0);
            flights.sort(sortByTime);
            if (flights.front().getTimestampEnd() > static_cast<long int>(time(0)) + timer.getAddedTime())
            {
                current_fly = flights.front();
                auto it = next(flights.begin(), 1);
                last_flight = *it;
            }
            else
                last_flight = flights.front();
            if (last_flight.getAirportId())
            {
                //Found airport from what plane took off
                long int last_flight_air_id = last_flight.getAirportId();
                list<AirportModel> airport1 = air.getAirports(&last_flight_air_id);
                if (airport1.empty())
                    throw 404;
                double x1 = airport1.front().getX(); //start airport coordinate x
                double y1 = airport1.front().getY(); //start airport coordinate y
                int speed = planes.front().getSpeed(); //plane speed
                if (current_fly.getId() != 0)
                {
                    //If we found current flight, we will find airport from that flight
                    long int current_flight_air_id = current_fly.getAirportId();
                    list<AirportModel> airport2 = air.getAirports(&current_flight_air_id);
                    if (airport2.empty())
                        throw 404;
                    double x2 = airport2.front().getX(); //end airport coordnate x
                    double y2 = airport2.front().getY(); //end airport coordinate y
                    double length = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)); //lenght of flight
                    long int elapsedTime = (timer.getAddedTime() + static_cast<long int>(time(0))) - current_fly.getTimestampStart();
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
            }
        } else
        {
            //If plane didn't fly yer, we take coordinates of airport, that first in list of airports.
            list<AirportModel> airport = air.getAirports();
            if (airport.empty())
                throw 404;
            planeResponse.setX(airport.front().getX());
            planeResponse.setY(airport.front().getY());
        }
        planesResponse.push_back(planeResponse);
    }
    return planesResponse;
}

bool PlaneService::createPlane(PlaneModel plane, string token)
{
    set<string> permissions;
    permissions.insert("createPlane");
    bool isAllowed = ident.authorize(permissions ,token);
    if (!isAllowed)
        throw 401;
    bool res = repo.createPlane(plane);
    return res;
}
bool PlaneService::deletePlane(long int id, string token)
{
    set<string> permissions;
    permissions.insert("deletePlane");
    bool isAllowed = ident.authorize(permissions ,token);
    if (!isAllowed)
        throw 401;
    list<FlightModel> flights = flight.getFlights();
    for (auto fly : flights)
    {
        if (fly.getPlaneId() == id)
        {
            if (fly.getTimestampEnd() >= timer.getAddedTime() + static_cast<long int>(time(0)))
                throw 409;
        }
    }
    bool res = repo.deletePlane(id);
    return res;
}
bool PlaneService::updatePlane(PlaneModel plane, set<string> update, string token)
{
    set<string> permissions;
    permissions.insert("updatePlane");
    bool isAllowed = ident.authorize(permissions ,token);
    if (!isAllowed)
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

