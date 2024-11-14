#include "../../header/controllers/AirportController.h"
#include "../../Config.h"
#include <json/single_include/nlohmann/json.hpp>
#include <string>

using namespace nlohmann;
using namespace httplib;
using namespace std;

void AirportController::configure(Server* server)
{
    // sample request handlers
    server->Get(AIRPORT_GET_ALL_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("User-Token");
            std::set<std::string> permissions = std::set<std::string>();
            pmr::list<AirportModel> airports = serv.getAllAirports(header, permissions);
            if (!airports.empty())
            {
                json airports_json = json::array();
                for (auto airport : airports) {
                    json airport_json;
                    airport_json["id"] = airport.getId();
                    airport_json["name"] = airport.getName();
                    airport_json["size"] = airport.getSize();
                    airport_json["x"] = airport.getX();
                    airport_json["y"] = airport.getY();
                    airports_json.push_back(airport_json);
                }
                res.status = 200;
                res.set_content(airports_json.dump(), "application/json");
            } else
            {
                res.status = 404;
                res.set_content("Аэропорты не найдены", "text/plain");
            }
        } catch (const runtime_error& e)
        {
            res.status = 401;
            res.set_content(e.what(), "text/plain");
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
            auto header = req.get_header_value("User-Token");
            std::set<std::string> permissions = std::set<std::string>();
            json result = json::parse(req.body);
            bool created = serv.createAirport(AirportModel(result["id"], result["name"], result["size"],  result["x"], result["y"]), header, permissions);
            if (created)
            {
                res.status = 201;
                res.set_content(result.dump(), "application/json");
            } else
            {
                res.status = 400;
                res.set_content("Не удалось создать аэропорт", "text/plane");
            }
        } catch (const runtime_error& e)
        {
            res.status = 401;
            res.set_content(e.what(), "text/plain");
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
            auto header = req.get_header_value("User-Token");
            std::set<std::string> permissions = std::set<std::string>();
            string fields = req.get_param_value("update");
            json result = json::parse(req.body);
            AirportModel airport(result["id"], result["name"], result["size"], result["x"], result["y"]);
            bool edited = serv.editAirport(airport, fields, header, permissions);
            if (edited)
            {
                res.status = 201;
                res.set_content("Обновлены поля " + fields + " у аэропорта с id" + to_string(airport.getId()), "text/plane");
            } else
            {
                res.status = 404;
                res.set_content("Не удалось обновить аэропорт", "text/plane");
            }
        } catch (const runtime_error& e)
        {
            res.status = 401;
            res.set_content(e.what(), "text/plain");
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
        auto header = req.get_header_value("User-Token");
        std::set<std::string> permissions = std::set<std::string>();
        int id = stoi(req.matches[1]);
        bool deleted = serv.deleteAirport(id, header, permissions);
        if (deleted)
        {
            res.status = 200;
        } else
        {
            res.status = 404;
            res.set_content("Аэропорт с таким id не найден", "text/plain");
        }
    } catch (const runtime_error& e)
    {
        res.status = 401;
        res.set_content(e.what(), "text/plain");
    } catch (const std::exception& e)
    {
        cout << "AirportController::AirportController: exception occured" << e.what() << endl;
        res.status = 500;
    }
});
    server->Get(AIRPORT_GET_BY_ID_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("User-Token");
            std::set<std::string> permissions = std::set<std::string>();
            int id = stoi(req.get_param_value("id"));
            cout << id << endl;
            AirportModel airport = serv.getAirportById(id, header, permissions);
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
                res.set_content("Не найден аэропорт с таким id", "text/plane");
            }
        } catch (const runtime_error& e)
        {
            res.status = 401;
            res.set_content(e.what(), "text/plain");
        } catch(const std::exception& e)
        {
            cout << "AirportController::AirportController: exception occured" << e.what() << endl;
            res.status = 500;
        }
    });
}
