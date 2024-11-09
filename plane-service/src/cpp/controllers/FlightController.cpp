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
            auto header = req.get_header_value("User-Token");
            std::set<std::string> permissions = std::set<std::string>();
            std::pmr::list<FlightModel> flights = serv.getAllFlights(header, permissions);
            if (!flights.empty())
            {
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
            } else
            {
                res.status = 404;
                res.set_content("Полеты не найдены", "text/plain");
            }
        } catch (const runtime_error& e)
        {
            res.status = 401;
            res.set_content(e.what(), "text/plain");
        } catch (const std::exception& e)
        {
            cout << "FlightController::FlightController: exception occured" << e.what() << endl;
            res.status = 500;
        }
    });
    server->Post(FLIGHT_CREATE_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("User-Token");
            std::set<std::string> permissions = std::set<std::string>();
            json flight_json = json::parse(req.body);
            FlightModel flight(flight_json["id"], flight_json["timestampStart"], flight_json["timestampEnd"], flight_json["dispatcherId"], flight_json["planeId"], flight_json["airportId"]);
            bool created = serv.createFlight(flight, header, permissions);
            if (created)
            {
                res.status = 201;
                res.set_content(flight_json.dump(), "application/json");
            } else
            {
                res.status = 400;
                res.set_content("Не удалось создать полет", "text/plain");
            }
        } catch (const runtime_error& e)
        {
            res.status = 401;
            res.set_content(e.what(), "text/plain");
        } catch (const std::exception& e)
        {
            cout << "FlightController::FlightController: exception occured" << e.what() << endl;
            res.status = 500;
        }
    });
    server->Get(FLIGHT_GET_BY_ID_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("User-Token");
            std::set<std::string> permissions = std::set<std::string>();
            int id = stoi(req.get_param_value("id"));
            FlightModel flight = serv.getFlightById(id, header, permissions);
            FlightModel empty_flight;
            if (flight.getId() != empty_flight.getId())
            {
                json flight_json;
                flight_json["id"] = flight.getId();
                flight_json["timestampStart"] = flight.getTimestampStart();
                flight_json["timestampEnd"] = flight.getTimestampEnd();
                flight_json["dispatcherId"] = flight.getDispatcherId();
                flight_json["planeId"] = flight.getPlaneId();
                flight_json["airportId"] = flight.getAirportId();
                res.status = 200;
                res.set_content(flight_json.dump(), "application/json");
            } else
            {
                res.status = 404;
                res.set_content("Полет с таким id не найден", "text/plain");
            }
        } catch (const runtime_error& e)
        {
            res.status = 401;
            res.set_content(e.what(), "text/plain");
        } catch (const std::exception& e)
        {
            cout << "FlightController::FlightController: exception occured" << e.what() << endl;
            res.status = 500;
        }
    });
}