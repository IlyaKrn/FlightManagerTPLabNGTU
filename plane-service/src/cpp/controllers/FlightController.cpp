#include "../../header/controllers/FlightController.h"
#include "../../Config.h"
#include <json/single_include/nlohmann/json.hpp>



using namespace nlohmann;
using namespace httplib;
using namespace std;
bool FlightsContainsNullFields(json req_body)
{
    return req_body["id"].is_null()
    || req_body["timestampStart"].is_null()
    || req_body["timestampEnd"].is_null()
    || req_body["planeId"].is_null()
    || req_body["airportId"].is_null()
    || req_body["dispatcherId"].is_null();
}

void FlightController::configure(Server* server)
{
    // sample request handlers
    server->Get(FLIGHT_GET_ALL_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE)
                res.status = 403;
            list<FlightModel> flights = serv.getAllFlights(header);
            json flights_json = json::array();
            for (auto flight : flights)
            {
                json flight_json;
                flight_json["id"] = flight.getId();
                flight_json["timestampStart"] = flight.getTimestampStart();
                flight_json["timestampEnd"] = flight.getTimestampEnd();
                flight_json["dispatcherId"] = flight.getDispatcherId();
                flight_json["planeId"] = flight.getPlaneId();
                flight_json["airportId"] = flight.getAirportId();
                flights_json.push_back(flight_json);
            }
            res.status = 200;
            res.set_content(flights_json.dump(), "application/json");
        } catch (int& e)
        {
            cout << "exception occured " << e << endl;
            res.status = e;
        } catch (const exception& e)
        {
            cout << "exception occured" << e.what() << endl;
            res.status = 500;
        }
    });
    server->Post(FLIGHT_CREATE_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE)
                res.status = 403;
            json request = json::parse(req.body);
            if (FlightsContainsNullFields(request))
                throw 400;
            FlightModel flight(request["id"], request["timestampStart"], request["timestampEnd"], request["dispatcherId"], request["planeId"], request["airportId"]);
            FlightModel created = serv.createFlight(flight, header);
            json flight_json;
            flight_json["id"] = created.getId();
            flight_json["timestampStart"] = created.getTimestampStart();
            flight_json["timestampEnd"] = created.getTimestampEnd();
            flight_json["dispatcherId"] = created.getDispatcherId();
            flight_json["planeId"] = created.getPlaneId();
            flight_json["airportId"] = created.getAirportId();
            res.status = 200;
            res.set_content(flight_json.dump(), "application/json");
        } catch (int& e)
        {
            cout << "exception occured " << e << endl;
            res.status = e;
        } catch (const exception& e)
        {
            cout << "exception occured" << e.what() << endl;
            res.status = 500;
        }
    });
}