#include "../../header/controllers/PlaneController.h"
#include "../../Config.h"
#include <json/single_include/nlohmann/json.hpp>



using namespace nlohmann;
using namespace httplib;
using namespace std;
bool PlaneContainsNullFields(json req_body)
{
    return req_body["id"].is_null()
    || req_body["name"].is_null()
    || req_body["builtYear"].is_null()
    || req_body["brokenPercentage"].is_null()
    || req_body["pilot"].is_null()
    || req_body["minAirportSize"].is_null()
    || req_body["speed"].is_null();
}
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
            json request = json::parse(req.body);
            if (PlaneContainsNullFields(request))
                throw 400;
            PlaneModel plane(request["id"], request["name"], request["pilot"], request["builtYear"], request["brokenPercentage"], request["speed"], request["minAirportSize"]);
            PlaneModel created = serv.createPlane(plane, header);
            json plane_json;
            plane_json["id"] = created.getId();
            plane_json["name"] = created.getName();
            plane_json["pilot"] = created.getPilot();
            plane_json["builtYear"] = created.getBuiltYear();
            plane_json["brokenPercentage"] = created.getBrokenPercentage();
            plane_json["speed"] = created.getSpeed();
            plane_json["minAirportSize"] = created.getMinAirportSize();
            res.status = 200;
            res.set_content(plane_json.dump(), "application/json");
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
            if (fields.empty())
                throw 400;
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
            json request = json::parse(req.body);
            for (auto update : updates)
            {
                if (request[update].is_null())
                    throw 400;
            }
            string name, pilot;
            int builtYear, brokenPercentage, speed, minAirportSize;
            if (!request["name"].is_null()) name = request["name"]; else name = "string";
            if (!request["pilot"].is_null()) pilot = request["pilot"]; else pilot = "string";
            if (!request["builtYear"].is_null()) builtYear = request["builtYear"]; else builtYear = 0;
            if (!request["brokenPercentage"].is_null()) brokenPercentage = request["brokenPercentage"]; else brokenPercentage = 0;
            if (!request["speed"].is_null()) speed = request["speed"]; else speed = 0;
            if (!request["minAirportSize"].is_null()) minAirportSize = request["minAirportSize"]; else minAirportSize = 0;
            PlaneModel plane(request["id"], name, pilot, builtYear, brokenPercentage, speed, minAirportSize);
            PlaneModel updated = serv.updatePlane(plane, updates, header);
            updates.clear();
            json plane_json;
            plane_json["id"] = updated.getId();
            plane_json["name"] = updated.getName();
            plane_json["pilot"] = updated.getPilot();
            plane_json["builtYear"] = updated.getBuiltYear();
            plane_json["brokenPercentage"] = updated.getBrokenPercentage();
            plane_json["speed"] = updated.getSpeed();
            plane_json["minAirportSize"] = updated.getMinAirportSize();
            res.status = 200;
            res.set_content(plane_json.dump(), "application/json");
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
    server->Delete(PLANE_DELETE_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE)
                res.status = 403;
            long int id = stol(req.get_param_value("id"));
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
