#include "../../header/controllers/DispatcherController.h"
#include "../../Config.h"
#include <json/single_include/nlohmann/json.hpp>



using namespace nlohmann;
using namespace httplib;
using namespace std;

void DispatcherController::configure(Server* server)
{
    // sample request handlers
    server->Get(DISPATCHER_GET_ALL_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_param_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE)
                res.status = 403;
            list<DispatcherModel> dispatchers = serv.getAllDispatchers(header);
            json result = json::array();
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
                result.push_back(dispatcher_json);
            }
            res.set_content(result.dump(), "application/json");
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
            string service_token = req.get_param_value("Service-Token");
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
            set<RoleModel> roles;
            for (auto role : result["roles"])
            {
                if (role == "ADMIN")
                {
                    roles.insert(RoleModel::ADMIN);
                } else if (role == "DISPATCHER")
                {
                    roles.insert(RoleModel::DISPATCHER);
                }
            }
            bool isBanned = result["isBanned"];
            DispatcherModel dispatcher(result["id"], result["firstName"], result["lastName"], result["email"], result["password"], isBanned, roles);
            bool updated = serv.updateDispatcher(dispatcher, updates, header);
            updates.clear();
            if (updated)
            {
                res.status = 200;
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
    server->Get(DISPATCHER_GET_BY_ID_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_param_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE)
                res.status = 403;
            int id = stoi(req.get_param_value("id"));
            DispatcherModel dispatcher = serv.getDispatcherById(id, header);
            json result;
            result["id"] = dispatcher.getId();
            result["firstName"] = dispatcher.getFirstname();
            result["lastName"] = dispatcher.getLastname();
            result["email"] = dispatcher.getEmail();
            result["password"] = dispatcher.getPassword();
            result["isBanned"] = dispatcher.getIsBanned();
            result["roles"] = json::array();
            for (auto role: dispatcher.getRoles())
            {
                switch (role)
                {
                case RoleModel::ADMIN: result["roles"].push_back("ADMIN");
                case RoleModel::DISPATCHER: result["roles"].push_back("DISPATCHER");
                }
            }
            res.status = 200;
            res.set_content(result.dump(), "application/json");
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
