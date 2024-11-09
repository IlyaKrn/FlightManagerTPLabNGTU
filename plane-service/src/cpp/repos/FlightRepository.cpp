#include "../../header/repos/FlightRepository.h"
#include <cpp-httplib/httplib.h>
#include "../../Config.h"
std::pmr::list<FlightModel> FlightRepository::getFlights(std::string id)
{
    httplib::Client cli(DATABASE_SERVICE_HOST, DATABASE_SERVICE_PORT);

    httplib::Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    httplib::Params params = {
        {"id", id }
    };
    auto res = cli.Get(FLIGHT_GET_BY_ID_MAPPING, params, headers);
    if (res->status == 200)
    {
        nlohmann::json flights_json = nlohmann::json::parse(res->body);
        std::pmr::list<FlightModel> flights;
        for (auto item : flights_json)
        {
            FlightModel flight(item["id"], item["timestampStart"], item["timestampEnd"], item["dispatcherId"], item["planeId"], item["airportId"]);
            flights.push_back(flight);
        }
        return flights;
    }
    return std::pmr::list<FlightModel>();
}

bool FlightRepository::createFlight(FlightModel flight)
{
    httplib::Client cli(DATABASE_SERVICE_HOST, DATABASE_SERVICE_PORT);

    httplib::Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    nlohmann::json flight_json;
    flight_json["id"] = flight.getId();
    flight_json["timestampStart"] = flight.getTimestampStart();
    flight_json["timestampEnd"] = flight.getTimestampEnd();
    flight_json["dispatcherId"] = flight.getDispatcherId();
    flight_json["planeId"] = flight.getPlaneId();
    flight_json["airportId"] = flight.getAirportId();
    auto res = cli.Post(FLIGHT_CREATE_MAPPING, headers, flight_json.dump(), "application/json");
    if (res->status == 200)
    {
        return true;
    }
    return false;
}

