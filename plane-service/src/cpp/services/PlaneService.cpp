#include "../../header/services/PlaneService.h"
#include "../../header/models/PlaneModelResponse.h"
#include <cmath>
#include "../../header/services/FlightService.h"
#include "../../header/services/AirportService.h"
#include "../../header/services/TimeService.h"

using namespace std;
list<PlaneModelResponse> PlaneService::getAllPlanes(string token)
{
    try
    {
        set<string> permissions;
        permissions.insert("getAllPlanes");
        bool isAllowed = ident.authorize(permissions ,token);
        if (!isAllowed)
        {
            throw string("401");
        }
        list<PlaneModel> planes = repo.getPlanes();
        list<PlaneModelResponse> planesResponse;
        for (auto plane : planes)
        {
            PlaneModelResponse planeResponse(plane.getId(), plane.getName(), plane.getPilot(), plane.getBuiltYear(), plane.getBrokenPercentage(), plane.getSpeed(), plane.getMinAirportSize(), 0, 0);
            planesResponse.push_back(planeResponse);
        }
        return planesResponse;
    } catch (const string& e)
    {
        throw string(e);
    }
}
PlaneModelResponse PlaneService::getPlaneById(long int id, string token)
{
    try
    {
        set<string> permissions;
        permissions.insert("getPlaneById");
        bool isAllowed = ident.authorize(permissions ,token);
        if (!isAllowed)
        {
            throw string("401");
        }
        list<PlaneModel> planes = repo.getPlanes(&id);
        PlaneModelResponse planeResponse(planes.front().getId(), planes.front().getName(), planes.front().getPilot(), planes.front().getBuiltYear(), planes.front().getBrokenPercentage(), planes.front().getSpeed(), planes.front().getMinAirportSize(), 0, 0);
        return planeResponse;
    } catch (const string& e)
    {
        throw string(e);
    }
}
bool PlaneService::createPlane(PlaneModel plane, string token)
{
    try
    {
        set<string> permissions;
        permissions.insert("createPlane");
        bool isAllowed = ident.authorize(permissions ,token);
        if (!isAllowed)
        {
            throw string("401");
        }
        bool res = repo.createPlane(plane);
        return res;
    } catch (const string& e)
    {
        throw string(e);
    }
}
bool PlaneService::deletePlane(long int id, string token)
{
    try
    {
        set<string> permissions;
        permissions.insert("deletePlane");
        bool isAllowed = ident.authorize(permissions ,token);
        if (!isAllowed)
        {
            throw string("401");
        }
        bool res = repo.deletePlane(id);
        return res;
    } catch (const string& e)
    {
        throw string(e);
    }
}
bool PlaneService::updatePlane(PlaneModel plane, set<string> update, string token)
{
    try
    {
        set<string> permissions;
        permissions.insert("updatePlane");
        bool isAllowed = ident.authorize(permissions ,token);
        if (!isAllowed)
        {
            throw string("401");
        }
        PlaneModelResponse nplane = getPlaneById(plane.getId(), token);
        PlaneModel n_plane(nplane.getId(), nplane.getName(), nplane.getPilot(), nplane.getBuiltYear(), nplane.getBrokenPercentage(), nplane.getSpeed(), nplane.getMinAirportSize());
        if (update.count("name") > 0)
        {
            n_plane.setName(plane.getName());
        }
        if (update.count("pilot") > 0)
        {
            n_plane.setPilot(plane.getPilot());
        }
        if (update.count("builtYear") > 0)
        {
            n_plane.setBuiltYear(plane.getBuiltYear());
        }
        if (update.count("brokenPercentage") > 0)
        {
            n_plane.setBrokenPercentage(plane.getBrokenPercentage());
        }
        if (update.count("speed") > 0)
        {
            n_plane.setSpeed(plane.getSpeed());
        }
        if (update.count("minAirportSize") > 0)
        {
            n_plane.setMinAirportSize(plane.getMinAirportSize());
        }
        bool res = repo.updatePlane(n_plane, update);
        return res;
    } catch (const string& e)
    {
        throw string(e);
    }
}
FlightService flightServ;
AirportService airServ;
TimeService timer;
PlaneModelResponse PlaneService::getPlaneCoordinates(PlaneModelResponse plane, string token)
{
    try
    {
        set<string> permissions;
        permissions.insert("getPlaneCoordinates");
        bool isAllowed = ident.authorize(permissions ,token);
        if (!isAllowed)
        {
            throw string("401");
        }
        list<FlightModel> flights = flightServ.getAllFlights(token);
        list<FlightModel> new_flights;
        for (auto flight : flights)
        {
            if (flight.getPlaneId() == plane.getId())
                new_flights.push_back(flight);
        }
        if (!new_flights.empty())
        {
            long int last_flight_time = 0;
            FlightModel last_flight(0,0,0,0,0,0);
            FlightModel current_fly(0,0,0,0,0,0);
            for (auto flight : new_flights)
            {
                if (flight.getTimestampEnd() > last_flight_time)
                {
                    if (flight.getTimestampStart() < timer.getCurrentTime())
                    {
                        last_flight_time = flight.getTimestampEnd();
                        last_flight = flight;
                    } else
                    {
                        current_fly = flight;
                    }
                }
            }
            if (last_flight.getAirportId())
            {
                AirportModel airport1 = airServ.getAirportById(last_flight.getAirportId(), token);
                double x1 = airport1.getX();
                double y1 = airport1.getY();
                int speed = plane.getSpeed();
                if (current_fly.getId() != 0)
                {
                    AirportModel airport2 = airServ.getAirportById(current_fly.getAirportId(), token);
                    double x2 = airport2.getX();
                    double y2 = airport2.getY();
                    double length = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
                    long int elapsedTime = timer.getCurrentTime() - current_fly.getTimestampStart();

                    double newX = x1 + (x2 - x1) * (speed * elapsedTime / length);
                    double newY = y1 + (y2 - y1) * (speed * elapsedTime / length);
                    plane.setX(newX);
                    plane.setY(newY);
                    return plane;
                }
                plane.setX(x1);
                plane.setY(y1);
                return plane;
            }
        }
        AirportModel airport = airServ.getAirportById(flights.front().getAirportId(), token);
        plane.setX(airport.getX());
        plane.setY(airport.getY());
        return plane;
    } catch (const string& e)
    {
        throw string(e);
    }
}