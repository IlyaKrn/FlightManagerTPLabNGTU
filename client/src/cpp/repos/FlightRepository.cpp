#include "../../header/repos/FlightRepository.h"

#include <cpp-httplib/httplib.h>
#include <json/single_include/nlohmann/json.hpp>

#include "../../Config.h"
using namespace std;
using namespace httplib;
using namespace nlohmann;

list<FlightModel> FlightRepository::getAllFlights(string token)
{
    Client cli(GATEWAY_HOST, GATEWAY_PORT);

    Headers headers = {
        { AUTH_TOKEN_NAME, token }
    };

    auto res = cli.Get(FLIGHT_GET_ALL_MAPPING, headers);
    if (res->status >= 200 && res->status < 300)
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
    throw res->status;
}

bool FlightRepository::createFlight(FlightModel flight, string token)
{
    Client cli(GATEWAY_HOST, GATEWAY_PORT);

    Headers headers = {
        { AUTH_TOKEN_NAME, token }
    };
    json flight_json;
    flight_json["id"] = flight.getId();
    flight_json["timestampStart"] = flight.getTimestampStart();
    flight_json["timestampEnd"] = flight.getTimestampEnd();
    flight_json["dispatcherId"] = flight.getDispatcherId();
    flight_json["planeId"] = flight.getPlaneId();
    flight_json["airportId"] = flight.getAirportId();
    auto res = cli.Post(FLIGHT_CREATE_MAPPING, headers, flight_json.dump(), "application/json");
    if (res->status >= 200 && res->status < 300)
        return true;
    throw res->status;
}