#include "../../header/controllers/FlightController.h"
#include "../../Config.h"
#include <json/single_include/nlohmann/json.hpp>



using namespace nlohmann;
using namespace httplib;
using namespace std;

void FlightController::configure(Server* server)
{
    // sample request handlers
    server->Get(FLIGHT_GET_ALL_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            list<FlightModel> flights = serv.getAllFlights(header);
            json result = json::array();
            for (auto flight : flights)
            {
                json flight_json;
                flight_json["id"] = flight.getId();
                flight_json["timestampStart"] = flight.getTimestampStart();
                flight_json["timestampEnd"] = flight.getTimestampEnd();
                flight_json["dispatcherId"] = flight.getDispatcherId();
                flight_json["planeId"] = flight.getPlaneId();
                flight_json["airportId"] = flight.getAirportId();
                result.push_back(flight_json);
            }
            res.status = 200;
            res.set_content(result.dump(), "application/json");
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
            json flight_json = json::parse(req.body);
            FlightModel flight(flight_json["id"], flight_json["timestampStart"], flight_json["timestampEnd"], flight_json["dispatcherId"], flight_json["planeId"], flight_json["airportId"]);
            bool created = serv.createFlight(flight, header);
            if (created)
            {
                res.status = 200;
                res.set_content(flight_json.dump(), "application/json");
            }
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
    server->Get(FLIGHT_GET_BY_ID_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            int id = stoi(req.get_param_value("id"));
            FlightModel flight = serv.getFlightById(id, header);
            json flight_json;
            flight_json["id"] = flight.getId();
            flight_json["timestampStart"] = flight.getTimestampStart();
            flight_json["timestampEnd"] = flight.getTimestampEnd();
            flight_json["dispatcherId"] = flight.getDispatcherId();
            flight_json["planeId"] = flight.getPlaneId();
            flight_json["airportId"] = flight.getAirportId();
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