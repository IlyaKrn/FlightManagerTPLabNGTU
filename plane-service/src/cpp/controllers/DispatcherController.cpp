#include "../../header/controllers/DispatcherController.h"
#include "../../Config.h"
#include <json/single_include/nlohmann/json.hpp>



using namespace nlohmann;
using namespace httplib;
using namespace std;

bool DispatcherContainsNullFields(json req_body)
{
    return req_body["id"].is_null()
    || req_body["firstName"].is_null()
    || req_body["lastName"].is_null()
    || req_body["email"].is_null()
    || req_body["password"].is_null()
    || req_body["isBanned"].is_null()
    || req_body["roles"].is_null();
}

void DispatcherController::configure(Server* server)
{
    // sample request handlers
    server->Get(DISPATCHER_GET_ALL_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE)
                res.status = 403;
            list<DispatcherModel> dispatchers = serv.getAllDispatchers(header);
            json dispatchers_json = json::array();
            for (auto dispatcher : dispatchers)
            {
                json dispatcher_json;
                dispatcher_json["id"] = dispatcher.getId();
                dispatcher_json["firstName"] = dispatcher.getFirstname();
                dispatcher_json["lastName"] = dispatcher.getLastname();
                dispatcher_json["email"] = dispatcher.getEmail();
                dispatcher_json["password"] = dispatcher.getPassword();
                dispatcher_json["isBanned"] = dispatcher.getIsBanned();
                dispatcher_json["roles"] = json::array();
                for (auto role: dispatcher.getRoles())
                {
                    switch (role)
                    {
                    case RoleModel::ADMIN: dispatcher_json["roles"].push_back("ADMIN");
                    case RoleModel::DISPATCHER: dispatcher_json["roles"].push_back("DISPATCHER");
                    }
                }
                dispatchers_json.push_back(dispatcher_json);
            }
            res.set_content(dispatchers_json.dump(), "application/json");
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
    server->Post(DISPATCHER_UPDATE_MAPPING, [&](const Request& req, Response& res)
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
            set<RoleModel> roles;
            if (!request["roles"].is_null())
            {
                for (auto role : request["roles"])
                {
                    if (role == "ADMIN")
                        roles.insert(RoleModel::ADMIN);
                    else if (role == "DISPATCHER")
                        roles.insert(RoleModel::DISPATCHER);
                }
            } else
                roles = set<RoleModel>();
            bool isBanned;
            string firstName, lastName, email, password;
            if (!request["isBanned"].is_null()) isBanned = request["isBanned"]; else isBanned = false;
            if (!request["lastName"].is_null()) lastName = request["lastName"]; else lastName = "string";
            if (!request["firstName"].is_null()) firstName = request["firstName"]; else firstName = "string";
            if (!request["email"].is_null()) email = request["email"]; else email = "string";
            if (!request["password"].is_null()) password = request["password"]; else password = "string";
            DispatcherModel dispatcher(request["id"], firstName, lastName, email, password, isBanned, roles);
            DispatcherModel updated = serv.updateDispatcher(dispatcher, updates, header);
            updates.clear();
            json dispatcher_json;
            dispatcher_json["id"] = dispatcher.getId();
            dispatcher_json["firstName"] = dispatcher.getFirstname();
            dispatcher_json["lastName"] = dispatcher.getLastname();
            dispatcher_json["email"] = dispatcher.getEmail();
            dispatcher_json["password"] = dispatcher.getPassword();
            dispatcher_json["isBanned"] = dispatcher.getIsBanned();
            dispatcher_json["roles"] = json::array();
            for (auto role: dispatcher.getRoles())
            {
                switch (role)
                {
                case RoleModel::ADMIN: dispatcher_json["roles"].push_back("ADMIN");
                case RoleModel::DISPATCHER: dispatcher_json["roles"].push_back("DISPATCHER");
                }
            }
            res.status = 200;
            res.set_content(dispatcher_json.dump(), "application/json");
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
    server->Get(DISPATCHER_GET_BY_ID_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            auto isPrivate = req.get_param_value("private");
            if (service_token != SERVICE_TOKEN_VALUE)
                res.status = 403;
            int id = stoi(req.get_param_value("id"));
            DispatcherModel dispatcher = serv.getDispatcherById(id, header, isPrivate == "true");
            json dispatcher_json;
            dispatcher_json["id"] = dispatcher.getId();
            dispatcher_json["firstName"] = dispatcher.getFirstname();
            dispatcher_json["lastName"] = dispatcher.getLastname();
            dispatcher_json["email"] = dispatcher.getEmail();
            dispatcher_json["password"] = dispatcher.getPassword();
            dispatcher_json["isBanned"] = dispatcher.getIsBanned();
            dispatcher_json["roles"] = json::array();
            for (auto role: dispatcher.getRoles())
            {
                switch (role)
                {
                case RoleModel::ADMIN: dispatcher_json["roles"].push_back("ADMIN");
                case RoleModel::DISPATCHER: dispatcher_json["roles"].push_back("DISPATCHER");
                }
            }
            res.status = 200;
            res.set_content(dispatcher_json.dump(), "application/json");
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
