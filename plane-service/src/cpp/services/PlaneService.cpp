#include "../../header/services/PlaneService.h"
#include "../../header/models/PlaneModelResponse.h"
#include <cmath>


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
        PlaneModelResponse planeResponse(plane.getId(), plane.getName(), plane.getPilot(), plane.getBuiltYear(), plane.getBrokenPercentage(), plane.getSpeed(), plane.getMinAirportSize(), 0, 0);
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
                    if (flight.getTimestampStart() < timer.getCurrentTime(token))
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
                int speed = planeResponse.getSpeed();
                if (current_fly.getId() != 0)
                {
                    AirportModel airport2 = airServ.getAirportById(current_fly.getAirportId(), token);
                    double x2 = airport2.getX();
                    double y2 = airport2.getY();
                    double length = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
                    long int elapsedTime = timer.getCurrentTime(token) - current_fly.getTimestampStart();

                    double newX = x1 + (x2 - x1) * (speed * elapsedTime / length);
                    double newY = y1 + (y2 - y1) * (speed * elapsedTime / length);
                    planeResponse.setX(newX);
                    planeResponse.setY(newY);
                } else
                {
                    planeResponse.setX(x1);
                    planeResponse.setY(y1);
                }
            }
        } else
        {
            AirportModel airport = airServ.getAirportById(flights.front().getAirportId(), token);
            planeResponse.setX(airport.getX());
            planeResponse.setY(airport.getY());
        }
        planesResponse.push_back(planeResponse);
    }
    return planesResponse;
}

PlaneModelResponse PlaneService::getPlaneById(long int id, string token)
{
    set<string> permissions;
    permissions.insert("getPlaneById");
    bool isAllowed = ident.authorize(permissions ,token);
    if (!isAllowed)
            throw 401;
    list<PlaneModel> planes = repo.getPlanes(&id);
    PlaneModelResponse planeResponse(planes.front().getId(), planes.front().getName(), planes.front().getPilot(), planes.front().getBuiltYear(), planes.front().getBrokenPercentage(), planes.front().getSpeed(), planes.front().getMinAirportSize(), 0, 0);
    list<FlightModel> flights = flightServ.getAllFlights(token);
    list<FlightModel> new_flights;
    for (auto flight : flights)
    {
        if (flight.getPlaneId() == planes.front().getId())
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
                if (flight.getTimestampStart() < timer.getCurrentTime(token))
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
            int speed = planes.front().getSpeed();
            if (current_fly.getId() != 0)
            {
                AirportModel airport2 = airServ.getAirportById(current_fly.getAirportId(), token);
                double x2 = airport2.getX();
                double y2 = airport2.getY();
                double length = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
                long int elapsedTime = timer.getCurrentTime(token) - current_fly.getTimestampStart();

                double newX = x1 + (x2 - x1) * (speed * elapsedTime / length);
                double newY = y1 + (y2 - y1) * (speed * elapsedTime / length);
                planeResponse.setX(newX);
                planeResponse.setY(newY);
            } else
            {
                planeResponse.setX(x1);
                planeResponse.setY(y1);
            }
        }
    } else
    {
        AirportModel airport = airServ.getAirportById(flights.front().getAirportId(), token);
        planeResponse.setX(airport.getX());
        planeResponse.setY(airport.getY());
    }
    return planeResponse;
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
    list<FlightModel> flights = flightServ.getAllFlights(token);
    for (auto fly : flights)
    {
        if (fly.getPlaneId() == id)
        {
            if (fly.getTimestampEnd() >= timer.getCurrentTime(token))
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
    PlaneModelResponse nplane = getPlaneById(plane.getId(), token);
    PlaneModel n_plane(nplane.getId(), nplane.getName(), nplane.getPilot(), nplane.getBuiltYear(), nplane.getBrokenPercentage(), nplane.getSpeed(), nplane.getMinAirportSize());
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

