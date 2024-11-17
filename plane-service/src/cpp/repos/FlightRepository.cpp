#include "../../header/repos/FlightRepository.h"
#include <cpp-httplib/httplib.h>
#include "../../Config.h"
#include <json/single_include/nlohmann/json.hpp>

using namespace std;
using namespace httplib;
using namespace nlohmann;
list<FlightModel> FlightRepository::getFlights(long int* id, long int* timestampStart, long int* timestampEnd, long int* dispatcherId, long int* planeId, long int* airportId)
{
    Client cli(DATABASE_SERVICE_HOST, DATABASE_SERVICE_PORT);

    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    Params params;
    if (id != nullptr)
        params.insert(make_pair("id", to_string(*id)));
    if (timestampStart != nullptr)
        params.insert(make_pair("timestampStart", to_string(*timestampStart)));
    if (timestampEnd != nullptr)
        params.insert(make_pair("timestampEnd", to_string(*timestampEnd)));
    if (dispatcherId != nullptr)
        params.insert(make_pair("dispatcherId", to_string(*dispatcherId)));
    if (planeId != nullptr)
        params.insert(make_pair("planeId", to_string(*planeId)));
    if (airportId != nullptr)
        params.insert(make_pair("airportId", to_string(*airportId)));
    auto res = cli.Get(FLIGHT_GET_BY_ID_MAPPING, params, headers);
    if (res->status == 200)
    {
        json flights_json = json::parse(res->body);
        list<FlightModel> flights;
        for (auto item : flights_json)
        {
            FlightModel flight(item["id"], item["timestampStart"], item["timestampEnd"], item["dispatcherId"], item["planeId"], item["airportId"]);
            flights.push_back(flight);
        }
        return flights;
    }
    throw string("500");
}

bool FlightRepository::createFlight(FlightModel flight)
{
    Client cli(DATABASE_SERVICE_HOST, DATABASE_SERVICE_PORT);

    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    json flight_json;
    flight_json["id"] = flight.getId();
    flight_json["timestampStart"] = flight.getTimestampStart();
    flight_json["timestampEnd"] = flight.getTimestampEnd();
    flight_json["dispatcherId"] = flight.getDispatcherId();
    flight_json["planeId"] = flight.getPlaneId();
    flight_json["airportId"] = flight.getAirportId();
    auto res = cli.Post(FLIGHT_CREATE_MAPPING, headers, flight_json.dump(), "application/json");
    if (res->status == 200)
        return true;
    if (res->status == 400)
        throw string("400");
    throw string("500");
}
