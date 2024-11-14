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
            auto header = req.get_header_value("User-Token");
            std::set<std::string> permissions = std::set<std::string>();
            std::pmr::list<DispatcherModel> dispatchers = serv.getAllDispatchers(header, permissions);
            if (!dispatchers.empty())
            {
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
            } else
            {
                res.set_content("Диспетчеры не найдены", "text/plain");
                res.status = 404;
            }
        } catch (const runtime_error& e)
        {
            res.status = 401;
            res.set_content(e.what(), "text/plain");
        } catch (const std::exception &e)
        {
            cout << "DispatcherController::DispatcherController: exception occured" << e.what() << endl;
            res.status = 500;
        }
    });
    server->Post(DISPATCHER_UPDATE_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("User-Token");
            std::set<std::string> permissions = std::set<std::string>();
            std::string fields = req.get_param_value("update");
            json result = json::parse(req.body);
            std::set<RoleModel> roles;
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
            bool updated = serv.editDispatcher(dispatcher, fields, header, permissions);
            if (updated)
            {
                res.status = 200;
                res.set_content(result.dump(), "application/json");
            } else
            {
                res.status = 400;
                res.set_content("Не удалось обновить диспетчера", "text/plain");
            }
        } catch (const runtime_error& e)
        {
            res.status = 401;
            res.set_content(e.what(), "text/plain");
        } catch (const std::exception& e)
        {
            cout << "DispatcherController::DispatcherController: exception occured" << e.what() << endl;
            res.status = 500;
        }
    });
    server->Get(DISPATCHER_GET_BY_ID_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("User-Token");
            std::set<std::string> permissions = std::set<std::string>();
            int id = stoi(req.get_param_value("id"));
            DispatcherModel dispatcher = serv.getDispatcherById(id, header, permissions);
            DispatcherModel empty_dispatcher;
            if (dispatcher.getId() != empty_dispatcher.getId())
            {
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
            } else
            {
                res.status = 404;
                res.set_content("Не найден диспетчер с таким id", "text/plain");
            }
        } catch (const runtime_error& e)
        {
            res.status = 401;
            res.set_content(e.what(), "text/plain");
        } catch (const std::exception& e)
        {
            cout << "DispatcherController::DispatcherController: exception occured" << e.what() << endl;
            res.status = 500;
        }
    });
}
