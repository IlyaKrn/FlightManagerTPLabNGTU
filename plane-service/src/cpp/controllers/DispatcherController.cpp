#include "../../header/controllers/DispatcherController.h"
#include "../../header/Config.h"
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
            std::pmr::list<DispatcherModel> dispatchers = serv.getAllDispatchers();
            if (!dispatchers.empty())
            {
                json result = json::array();
                for (auto dispatcher : dispatchers)
                {
                    json dispatcher_json;
                    dispatcher_json["id"] = dispatcher.getId();
                    dispatcher_json["name"] = dispatcher.getName();
                    dispatcher_json["firstname"] = dispatcher.getFirstname();
                    dispatcher_json["lastname"] = dispatcher.getLastname();
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
            } else
            {
                res.set_content("Диспетчеры не найдены", "text/plane");
                res.status = 404;
            }
        }
        catch (const std::exception &e)
        {
            cout << "DispatcherController::DispatcherController: exception occured" << e.what() << endl;
            res.status = 500;
        }
    });
    server->Post(DISPATCHER_UPDATE_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            std::string fields = req.get_param_value("update");
            json result = json::parse(req.body);
            std::set<RoleModel> roles;
            for (auto role : result["roles"])
            {
                if (role == "ADMIN")
                {
                    roles.insert(RoleModel::ADMIN);
                }
                if (role == "DISPATCHER")
                {
                    roles.insert(RoleModel::DISPATCHER);
                }
            }
            DispatcherModel dispatcher(result["id"], result["name"], result["firstname"], result["lastname"], result["email"], result["password"], result["isBanned"], roles);
            bool updated = serv.editDispatcher(dispatcher, fields);
            if (updated)
            {
                res.status = 200;
                res.set_content(result.dump(), "application/json");
            } else
            {
                res.status = 404;
                res.set_content("Не удалось обновить диспетчера", "text/plane");
            }
        }
        catch (const std::exception& e)
        {
            cout << "DispatcherController::DispatcherController: exception occured" << e.what() << endl;
            res.status = 500;
        }
    });
    server->Get(DISPATCHER_GET_BY_ID_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            int id = stoi(req.get_param_value("id"));
            DispatcherModel dispatcher = serv.getDispatcherById(id);
            DispatcherModel empty_dispatcher;
            if (dispatcher.getId() != empty_dispatcher.getId())
            {
                json result;
                result["id"] = dispatcher.getId();
                result["name"] = dispatcher.getName();
                result["firstname"] = dispatcher.getFirstname();
                result["lastname"] = dispatcher.getLastname();
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
            } else
            {
                res.status = 404;
                res.set_content("Не найден диспетчер с таким id", "text/plane");
            }
        }
        catch (const std::exception& e)
        {
            cout << "DispatcherController::DispatcherController: exception occured" << e.what() << endl;
            res.status = 500;
        }
    });
}
