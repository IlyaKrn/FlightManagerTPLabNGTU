#include "../../header/repos/DispatcherRepository.h"
#include "../../Config.h"
#include <cpp-httplib/httplib.h>
std::pmr::list<DispatcherModel> DispatcherRepository::getDispatchers(std::string id)
{
    httplib::Client cli(DATABASE_SERVICE_HOST, DATABASE_SERVICE_PORT);

    httplib::Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    httplib::Params params = {
        {"id", id }
    };
    auto res = cli.Get(DISPATCHER_GET_BY_ID_MAPPING, params, headers);
    if (res->status == 200)
    {
        nlohmann::json dispatcher_json = nlohmann::json::parse(res->body);
        std::pmr::list<DispatcherModel> result;
        for (auto item : dispatcher_json)
        {
            std::set<RoleModel> roles;
            for (auto role : item["roles"])
            {
                if (role == "ADMIN")
                {
                    roles.insert(RoleModel::ADMIN);
                } else if (role == "DISPATCHER")
                {
                    roles.insert(RoleModel::DISPATCHER);
                }
            }
            DispatcherModel dispatcher(item["id"], item["firstName"], item["lastName"], item["email"], item["password"], item["isBanned"], roles);
            result.push_back(dispatcher);
        }
        return result;
    }
    return std::pmr::list<DispatcherModel>();
}
bool DispatcherRepository::updateDispatchers(DispatcherModel dispatcher, std::string update)
{
    httplib::Client cli(DATABASE_SERVICE_HOST, DATABASE_SERVICE_PORT);

    httplib::Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    nlohmann::json dispatcher_json;
    dispatcher_json["id"] = dispatcher.getId();
    dispatcher_json["firstName"] = dispatcher.getFirstname();
    dispatcher_json["lastName"] = dispatcher.getLastname();
    dispatcher_json["email"] = dispatcher.getEmail();
    dispatcher_json["password"] = dispatcher.getPassword();
    dispatcher_json["isBanned"] = dispatcher.getIsBanned();
    dispatcher_json["roles"] = nlohmann::json::array();
    for (auto role : dispatcher.getRoles())
    {
        switch (role)
        {
            case RoleModel::ADMIN: dispatcher_json["roles"].push_back("ADMIN");
            case RoleModel::DISPATCHER: dispatcher_json["roles"].push_back("DISPATCHER");
        }
    }
    auto res = cli.Post(DISPATCHER_UPDATE_MAPPING + "?update" + update, headers, dispatcher_json.dump(), "application/json");
    if (res->status == 200)
    {
        return true;
    }
    return false;
}

