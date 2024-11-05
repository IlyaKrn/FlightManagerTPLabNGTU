#include "../../header/controllers/AirportController.h"
#include "../../header/Config.h"
#include <json/single_include/nlohmann/json.hpp>
#include <string>

using namespace nlohmann;
using namespace httplib;
using namespace std;

void AirportController::configure(Server* server)
{
    // sample request handlers
    server->Get(AIRPORT_GET_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            if (req.has_param("id")) {
                auto id = req.get_param_value("id");
                AirportModel airport = serv.getAirportById(stoi(id));
                AirportModel empty_airport;
                if (airport.getId() != empty_airport.getId())
                {
                    json airport_json;
                    airport_json["id"] = airport.getId();
                    airport_json["name"] = airport.getName();
                    airport_json["size"] = airport.getSize();
                    airport_json["x"] = airport.getX();
                    airport_json["y"] = airport.getY();
                    res.status = 200;
                    res.set_content(airport_json.dump(), "application/json");
                } else
                {
                    res.status = 404;
                    res.set_content("Аэропорт с таким id не найден", "text/plain");
                }
            } else {
                pmr::list<AirportModel> airports = serv.getAllAirports();
                if (!airports.empty())
                {
                    json airports_json = nlohmann::json::array();
                    for (auto airport : airports) {
                        json airport_json;
                        airport_json["id"] = airport.getId();
                        airport_json["name"] = airport.getName();
                        airport_json["size"] = airport.getSize();
                        airport_json["x"] = airport.getX();
                        airport_json["y"] = airport.getY();
                        airports_json.push_back(airport_json);
                    }
                    res.set_content(airports_json.dump(), "application/json");
                } else
                {
                    res.status = 404;
                    res.set_content("Аэропорты не найдены", "text/plain");
                }
            }
        } catch (const std::exception& e)
        {
            cout << "AirportController::AirportController: exception occured" << e.what() << endl;
            res.status = 500;
        }
    });

    server->Post(AIRPORT_CREATE_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            json result = json::parse(req.body);
            bool created = serv.createAirport(AirportModel(result["id"], result["name"], result["size"],  result["x"], result["y"]));
            if (created)
            {
                res.status = 201;
                res.set_content(result.dump(), "application/json");
            } else
            {
                res.status = 400;
                res.set_content("Не удалось создать аэропорт", "text/plane");
            }
        } catch (const std::exception& e)
        {
            cout << "AirportController::AirportController: exception occured" << e.what() << endl;
            res.status = 500;
        }
    });

    server->Post(AIRPORT_UPDATE_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            string fields = req.get_param_value("update");
            json result = json::parse(req.body);
            AirportModel airport(result["id"], result["name"], result["size"], result["x"], result["y"]);
            bool edited = serv.editAirport(airport, fields);
            if (edited)
            {
                res.status = 201;
                res.set_content("Обновлены поля " + fields + " у аэропорта с id" + to_string(airport.getId()), "text/plane");
            } else
            {
                res.status = 404;
                res.set_content("Не удалось обновить аэропорт", "text/plane");
            }
        } catch (const std::exception& e)
        {
            cout << "AirportController::AirportController: exception occured" << e.what() << endl;
            res.status = 500;
        }
    });

    server->Delete(AIRPORT_DELETE_MAPPING + R"(/(\d+))", [this](const Request& req, Response& res)
{
    try
    {
        int id = stoi(req.matches[1]);
        bool deleted = serv.deleteAirport(id);
        if (deleted)
        {
            res.status = 200;
        } else
        {
            res.status = 404;
            res.set_content("Аэропорт с таким id не найден", "text/plain");
        }
    } catch (const std::exception& e)
    {
        cout << "AirportController::AirportController: exception occured" << e.what() << endl;
        res.status = 500;
    }
});
}
