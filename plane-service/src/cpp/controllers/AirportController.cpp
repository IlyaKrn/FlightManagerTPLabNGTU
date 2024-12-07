#include "../../header/controllers/AirportController.h"
#include "../../Config.h"
#include <json/single_include/nlohmann/json.hpp>
#include <string>
#include <sstream>
using namespace nlohmann;
using namespace httplib;
using namespace std;

bool AirportContainsNullFields(json req_body)
{
    return req_body["id"].is_null()
    || req_body["name"].is_null()
    || req_body["size"].is_null()
    || req_body["x"].is_null()
    || req_body["y"].is_null();
}
void AirportController::configure(Server* server)
{
    // sample request handlers
    server->Get(AIRPORT_GET_ALL_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE)
                res.status = 403;
            list<AirportModel> airports = serv.getAllAirports(header);
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

    server->Post(AIRPORT_CREATE_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE)
                res.status = 403;
            json request = json::parse(req.body);
            if (AirportContainsNullFields(request))
                throw 400;
            AirportModel created = serv.createAirport(AirportModel(request["id"], request["name"], request["size"],  request["x"], request["y"]), header);
            json airport_json;
            airport_json["id"] = created.getId();
            airport_json["name"] = created.getName();
            airport_json["size"] = created.getSize();
            airport_json["x"] = created.getX();
            airport_json["y"] = created.getY();
            res.status = 201;
            res.set_content(airport_json.dump(), "application/json");
        }  catch (int& e)
        {
            cout << "exception occured " << e << endl;
            res.status = e;
        } catch (const exception& e)
        {
            cout << "exception occured" << e.what() << endl;
            res.status = 500;
        }
    });

    server->Post(AIRPORT_UPDATE_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string fields = req.get_param_value("update");
            if (fields.empty())
                throw 400;
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE)
                res.status = 403;
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
                if (request["id"].is_null())
                    throw 400;
                if (request[update].is_null())
                    throw 400;
            }
            string name;
            int size;
            double x, y;
            if (!request["name"].is_null()) name = request["name"]; else  name = "string";
            if (!request["size"].is_null()) size = request["size"]; else size = 0;
            if (!request["x"].is_null()) x = request["x"]; else  x = 0;
            if (!request["y"].is_null()) y = request["y"]; else  x = 0;
            AirportModel airport(request["id"], name, size, x, y);
            AirportModel updated = serv.updateAirport(airport, updates, header);
            updates.clear();
            json airport_json;
            airport_json["id"] = updated.getId();
            airport_json["name"] = updated.getName();
            airport_json["size"] = updated.getSize();
            airport_json["x"] = updated.getX();
            airport_json["y"] = updated.getY();
            res.status = 201;
            res.set_content(airport_json.dump(), "application/json");
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

    server->Delete(AIRPORT_DELETE_MAPPING, [this](const Request& req, Response& res)
{
    try
    {
        auto header = req.get_header_value("Authorization");
        string service_token = req.get_header_value("Service-Token");
        if (service_token != SERVICE_TOKEN_VALUE)
            res.status = 403;
        long int id = stol(req.get_param_value("id"));
        bool deleted = serv.deleteAirport(id, header);
        if (deleted)
            res.status = 200;
    }  catch (int& e)
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

