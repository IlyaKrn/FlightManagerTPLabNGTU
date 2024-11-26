#include "../../header/repos/DispatcherRepository.h"
#include "../../Config.h"
#include <cpp-httplib/httplib.h>
#include <json/single_include/nlohmann/json.hpp>

using namespace std;
using namespace httplib;
using namespace nlohmann;
list<DispatcherModel> DispatcherRepository::getDispatchers(long int* id, string* firstName, string* lastName, string* email, string* password, bool* isBanned, set<RoleModel*>* roles)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);

    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };

    Params params;
    if (id != nullptr)
        params.insert(make_pair("id", to_string(*id)));
    if (firstName != nullptr)
        params.insert(make_pair("firstName", *firstName));
    if (lastName != nullptr)
        params.insert(make_pair("lastName", *lastName));
    if (email != nullptr)
        params.insert(make_pair("email", *email));
    if (password != nullptr)
        params.insert(make_pair("password", *password));
    if (isBanned != nullptr)
        params.insert(make_pair("isBanned", to_string(*isBanned)));
    if (roles != nullptr)
        params.insert(make_pair("roles", "role"));
    auto res = cli.Get(DATABASE_DISPATCHER_GET_MAPPING, params, headers);
    if (res->status >= 200 && res->status < 300)
    {
        json dispatcher_json = json::parse(res->body);
        list<DispatcherModel> result;
        for (auto item : dispatcher_json)
        {
            set<RoleModel> Roles;
            for (auto Role : item["roles"])
            {
                if (Role == "ADMIN")
                    Roles.insert(RoleModel::ADMIN);
                else if (Role == "DISPATCHER")
                    Roles.insert(RoleModel::DISPATCHER);
            }
            DispatcherModel dispatcher(item["id"], item["firstName"], item["lastName"], item["email"], item["password"], item["isBanned"], Roles);
            result.push_back(dispatcher);
        }
        return result;
    }
    throw res->status;
}
bool DispatcherRepository::updateDispatchers(DispatcherModel dispatcher, set<string> updates)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);

    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    json dispatcher_json;
    dispatcher_json["id"] = dispatcher.getId();
    dispatcher_json["firstName"] = dispatcher.getFirstname();
    dispatcher_json["lastName"] = dispatcher.getLastname();
    dispatcher_json["email"] = dispatcher.getEmail();
    dispatcher_json["password"] = dispatcher.getPassword();
    dispatcher_json["isBanned"] = dispatcher.getIsBanned();
    dispatcher_json["roles"] = json::array();
    for (auto role : dispatcher.getRoles())
    {
        switch (role)
        {
            case RoleModel::ADMIN: dispatcher_json["roles"].push_back("ADMIN");
            case RoleModel::DISPATCHER: dispatcher_json["roles"].push_back("DISPATCHER");
        }
    }
    string update;
    for (auto item : updates)
    {
        if (update.empty())
            update = item;
        else
            update += "," + item;
    }
    auto res = cli.Post(DATABASE_DISPATCHER_UPDATE_MAPPING + "?update" + update, headers, dispatcher_json.dump(), "application/json");
    if (res->status >= 200 && res->status < 300)
        return true;
    throw res->status;
}

