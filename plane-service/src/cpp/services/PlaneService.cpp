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
    //Объяснение кода в getPlaneById
    list<PlaneModel> planes = repo.getPlanes();
    list<PlaneModelResponse> planesResponse;
    for (auto plane : planes)
    {
        PlaneModelResponse planeResponse(plane.getId(), plane.getName(), plane.getPilot(), plane.getBuiltYear(), plane.getBrokenPercentage(), plane.getSpeed(), plane.getMinAirportSize(), 0, 0);
        long int planeId = plane.getId();
        list<FlightModel> flights = flight.getFlights(nullptr, nullptr , nullptr, nullptr, &planeId);
        if (!flights.empty())
        {
            long int last_flight_time = 0;
            FlightModel last_flight(0,0,0,0,0,0);
            FlightModel current_fly(0,0,0,0,0,0);
            for (auto flight : flights)
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
                long int last_flight_air_id = last_flight.getAirportId();
                list<AirportModel> airport1 = air.getAirports(&last_flight_air_id);
                double x1 = airport1.front().getX();
                double y1 = airport1.front().getY();
                int speed = planeResponse.getSpeed();
                if (current_fly.getId() != 0)
                {
                    long int current_flight_air_id = current_fly.getAirportId();
                    list<AirportModel> airport2 = air.getAirports(&current_flight_air_id);
                    double x2 = airport2.front().getX();
                    double y2 = airport2.front().getY();
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
            long int air_id = flights.front().getAirportId();
            list<AirportModel> airport = air.getAirports(&air_id);
            planeResponse.setX(airport.front().getX());
            planeResponse.setY(airport.front().getY());
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
    //Создаем объект planeResponse
    PlaneModelResponse planeResponse(planes.front().getId(), planes.front().getName(), planes.front().getPilot(), planes.front().getBuiltYear(), planes.front().getBrokenPercentage(), planes.front().getSpeed(), planes.front().getMinAirportSize(), 0, 0);
    long int planeId = planes.front().getId();
    //Берем все полеты с участием данного самолета
    list<FlightModel> flights = flight.getFlights(nullptr, nullptr, nullptr, nullptr,&planeId);
    if (!flights.empty())
    {
        //Если найдены полеты, то ищем последний полет и, если есть, текущий полет
        long int last_flight_time = 0; //В эту переменную будет записано время последнего полета (не текущего)
        FlightModel last_flight(0,0,0,0,0,0);
        FlightModel current_fly(0,0,0,0,0,0);
        for (auto flight : flights)
        {
            //Здесь ищется последний полет (если найден исполняемый, то мы его сохраняем)
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
            //Находим аэропорт из которого вылетел самолет (его координаты x1, y1)
            long int last_flight_air_id = last_flight.getAirportId();
            list<AirportModel> airport1 = air.getAirports(&last_flight_air_id);
            double x1 = airport1.front().getX();
            double y1 = airport1.front().getY();
            //скорость самолета
            int speed = planes.front().getSpeed();
            if (current_fly.getId() != 0)
            {
                //Если найден текущий полет, то находим аэропорт из этого полета
                long int current_fly_air_id = current_fly.getAirportId();
                list<AirportModel> airport2 = air.getAirports(&current_fly_air_id);
                double x2 = airport2.front().getX();
                double y2 = airport2.front().getY();
                //Вычисляем длину пути и пройденное время с момента вылета
                double length = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
                long int elapsedTime = timer.getCurrentTime(token) - current_fly.getTimestampStart();
                //Вычисляем координаты самолета (формула взята из прошлой лабы)
                double newX = x1 + (x2 - x1) * (speed * elapsedTime / length);
                double newY = y1 + (y2 - y1) * (speed * elapsedTime / length);
                planeResponse.setX(newX);
                planeResponse.setY(newY);
            } else
            {
                //Если нет текущего полета, то записываем координаты аэропорта (в который прилетел самолет из его ласт пути)
                planeResponse.setX(x1);
                planeResponse.setY(y1);
            }
        }
    } else
    {
        //Если самолет не летал еще, то мы берем координаты первого аэропорта в списке аэропортов.
        long int airId = flights.front().getAirportId();
        list<AirportModel> airport = air.getAirports(&airId);
        planeResponse.setX(airport.front().getX());
        planeResponse.setY(airport.front().getY());
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
    list<FlightModel> flights = flight.getFlights();
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

