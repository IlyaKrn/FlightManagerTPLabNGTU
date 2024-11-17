#include "../../header/controllers/PlaneController.h"
#include "../../Config.h"
#include <json/single_include/nlohmann/json.hpp>



using namespace nlohmann;
using namespace httplib;
using namespace std;

void PlaneController::configure(Server* server)
{
    server->Get(PLANE_GET_ALL_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("User-Token");
            std::set<std::string> permissions = std::set<std::string>();
            pmr::list<PlaneModel> planes = serv.getAllPlanes(header, permissions);
            if (!planes.empty())
            {
                json planes_json = json::array();
                for (auto plane : planes)
                {
                    json plane_json;
                    plane_json["id"] = plane.getId();
                    plane_json["name"] = plane.getName();
                    plane_json["pilot"] = plane.getPilot();
                    plane_json["builtYear"] = plane.getBuiltYear();
                    plane_json["brokenPercentage"] = plane.getBrokenPercentage();
                    plane_json["speed"] = plane.getSpeed();
                    plane_json["minAirportSize"] = plane.getMinAirportSize();
                    planes_json.push_back(plane_json);
                }
                res.status = 200;
                res.set_content(planes_json.dump(), "application/json");
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
            cout << "PlaneController::PlaneController: exception occured" << e.what() << endl;
            res.status = 500;
        }
    });

    server->Post(PLANE_CREATE_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("User-Token");
            std::set<std::string> permissions = std::set<std::string>();
            json plane_json = json::parse(req.body);
            PlaneModel plane(plane_json["id"], plane_json["name"], plane_json["pilot"], plane_json["builtYear"], plane_json["brokenPercentage"], plane_json["speed"], plane_json["minAirportSize"]);
            bool created = serv.createPlane(plane, header, permissions);
            if (created)
            {
                res.status = 201;
                res.set_content(plane_json.dump(), "application/json");
            } else
            {
                res.status = 400;
                res.set_content("Не удалось создать аэропорт", "text/plain");
            }
        } catch (const runtime_error& e)
        {
            res.status = 401;
            res.set_content(e.what(), "text/plain");
        } catch (const std::exception& e)
        {
            cout << "PlaneController::PlaneController: exception occured" << e.what() << endl;
            res.status = 500;
        }
    });
    server->Post(PLANE_UPDATE_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("User-Token");
            std::set<std::string> permissions = std::set<std::string>();
            std::string fields = req.get_param_value("update");
            json plane_json = json::parse(req.body);
            PlaneModel plane(plane_json["id"], plane_json["name"], plane_json["pilot"], plane_json["builtYear"], plane_json["brokenPercentage"], plane_json["speed"], plane_json["minAirportSize"]);
            bool updated = serv.updatePlane(plane, fields, header, permissions);
            if (updated)
            {
                res.status = 200;
                res.set_content("Обновлены поля " + fields + " у самолёта с id " + std::to_string(plane.getId()), "text/plane");
            } else
            {
                res.status = 400;
                res.set_content("Не удалось обновить самолёт", "text/plain");
            }
        } catch (const runtime_error& e)
        {
            res.status = 401;
            res.set_content(e.what(), "text/plain");
        } catch (const std::exception& e)
        {
            cout << "PlaneController::PlaneController: exception occured" << e.what() << endl;
            res.status = 500;
        }
    });
    server->Delete(PLANE_DELETE_MAPPING + R"(/(\d+))", [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("User-Token");
            std::set<std::string> permissions = std::set<std::string>();
            int id = stoi(req.matches[1]);
            bool deleted = serv.deletePlane(id, header, permissions);
            if (deleted)
            {
                res.status = 200;
            } else
            {
                res.status = 404;
                res.set_content("Самолет с таким id не найден", "text/plain");
            }
        } catch (const runtime_error& e)
        {
            res.status = 401;
            res.set_content(e.what(), "text/plain");
        } catch (const std::exception& e)
        {
            cout << "PlaneController::PlaneController: exception occured" << e.what() << endl;
            res.status = 500;
        }
    });
    server->Get(PLANE_GET_BY_ID_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("User-Token");
            std::set<std::string> permissions = std::set<std::string>();
            int id = stoi(req.get_param_value("id"));
            PlaneModel plane = serv.getPlaneById(id, header, permissions);
            PlaneModel empty_plane;
            if (plane.getId() != empty_plane.getId())
            {
                json plane_json;
                plane_json["id"] = plane.getId();
                plane_json["name"] = plane.getName();
                plane_json["pilot"] = plane.getPilot();
                plane_json["builtYear"] = plane.getBuiltYear();
                plane_json["brokenPercentage"] = plane.getBrokenPercentage();
                plane_json["speed"] = plane.getSpeed();
                plane_json["minAirportSize"] = plane.getMinAirportSize();
                res.status = 200;
                res.set_content(plane_json.dump(), "application/json");
            } else
            {
                res.status = 404;
                res.set_content("Не найден самолет с таким id", "text/plain");
            }
        }
        catch (const runtime_error& e)
        {
            res.status = 401;
            res.set_content(e.what(), "text/plain");
        } catch (const std::exception& e)
        {
            cout << "PlaneController::PlaneController: exception occured" << e.what() << endl;
            res.status = 500;
        }
    });
}