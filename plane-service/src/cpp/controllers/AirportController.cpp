#include "../../header/controllers/AirportController.h"
#include "../../Config.h"
#include <json/single_include/nlohmann/json.hpp>
#include <string>
#include <sstream>
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
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_param_value("Service-Token");
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
            string service_token = req.get_param_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE)
                res.status = 403;
            json result = json::parse(req.body);
            bool created = serv.createAirport(AirportModel(result["id"], result["name"], result["size"],  result["x"], result["y"]), header);
            if (created)
            {
                res.status = 201;
                res.set_content(result.dump(), "application/json");
            }
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
            string service_token = req.get_param_value("Service-Token");
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
            json result = json::parse(req.body);
            AirportModel airport(result["id"], result["name"], result["size"], result["x"], result["y"]);
            bool updated = serv.updateAirport(airport, updates, header);
            updates.clear();
            if (updated)
            {
                res.status = 201;
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

    server->Delete(AIRPORT_DELETE_MAPPING + R"(/(\d+))", [this](const Request& req, Response& res)
{
    try
    {
        auto header = req.get_header_value("Authorization");
        string service_token = req.get_param_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE)
                res.status = 403;
        long int id = stol(req.matches[1]);
        bool deleted = serv.deleteAirport(id, header);
        if (deleted)
        {
            res.status = 200;
        }
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
    server->Get(AIRPORT_GET_BY_ID_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_param_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE)
                res.status = 403;
            int id = stoi(req.get_param_value("id"));
            AirportModel airport = serv.getAirportById(id, header);
            json airport_json;
            airport_json["id"] = airport.getId();
            airport_json["name"] = airport.getName();
            airport_json["size"] = airport.getSize();
            airport_json["x"] = airport.getX();
            airport_json["y"] = airport.getY();
            res.status = 200;
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
}
