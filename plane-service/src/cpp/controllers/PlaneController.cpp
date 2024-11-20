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
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE)
                res.status = 403;
            list<PlaneModelResponse> planes = serv.getAllPlanes(header);
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
                plane_json["x"] = plane.getX();
                plane_json["y"] = plane.getY();
                planes_json.push_back(plane_json);
            }
            res.status = 200;
            res.set_content(planes_json.dump(), "application/json");
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

    server->Post(PLANE_CREATE_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE)
                res.status = 403;
            json plane_json = json::parse(req.body);
            PlaneModel plane(plane_json["id"], plane_json["name"], plane_json["pilot"], plane_json["builtYear"], plane_json["brokenPercentage"], plane_json["speed"], plane_json["minAirportSize"]);
            bool created = serv.createPlane(plane, header);
            if (created)
            {
                res.status = 200;
                res.set_content(plane_json.dump(), "application/json");
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
    server->Post(PLANE_UPDATE_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE)
                res.status = 403;
            string fields = req.get_param_value("update");
            stringstream ss(fields);
            string item;
            set<string> updates;
            while (getline(ss, item, ','))
            {
                item.erase(0, item.find_first_not_of(" \n\r\t"));
                item.erase(item.find_last_not_of(" \n\r\t") + 1);
                if (!item.empty())
                    updates.insert(item);
            }
            json result = json::parse(req.body);
            PlaneModel plane(result["id"], result["name"], result["pilot"], result["builtYear"], result["brokenPercentage"], result["speed"], result["minAirportSize"]);
            bool updated = serv.updatePlane(plane, updates, header);
            updates.clear();
            if (updated)
            {
                res.status = 200;
                res.set_content(result.dump(), "application/json");
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
    server->Delete(PLANE_DELETE_MAPPING + R"(/(\d+))", [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE)
                res.status = 403;
            int id = stoi(req.matches[1]);
            bool deleted = serv.deletePlane(id, header);
            if (deleted)
            {
                res.status = 200;
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
}
