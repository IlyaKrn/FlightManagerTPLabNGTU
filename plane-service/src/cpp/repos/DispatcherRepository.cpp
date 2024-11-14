#include "../../header/repos/DispatcherRepository.h"
#include "../../Config.h"
#include <cpp-httplib/httplib.h>
#include <json/single_include/nlohmann/json.hpp>

using namespace std;
using namespace httplib;
using namespace nlohmann;
list<DispatcherModel> DispatcherRepository::getDispatchers(long int* id, string* firstName, string* lastName, string* email, string* password, bool* isBanned, set<RoleModel>* roles)
{
    Client cli(SERVER_HOST, DATABASE_SERVICE_PORT);

    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    string role;
    for (auto item : *roles)
    {
        if (item == RoleModel::ADMIN)
        {
            if (role.empty())
            {
                role += "ADMIN";
            } else
            {
                role += ",ADMIN";
            }
        }
        if (item == RoleModel::DISPATCHER)
        {
            if (role.empty())
            {
                role += "DISPATCHER";
            } else
            {
                role += ",DISPATCHER";
            }
        }
    }
    Params params;
    if (id)
    {
        params.insert(make_pair("id", to_string(*id)));
    }
    if (firstName)
    {
        params.insert(make_pair("firstName", *firstName));
    }
    if (lastName)
    {
        params.insert(make_pair("lastName", *lastName));
    }
    if (email)
    {
        params.insert(make_pair("email", *email));
    }
    if (password)
    {
        params.insert(make_pair("password", *password));
    }
    if (isBanned)
    {
        params.insert(make_pair("isBanned", to_string(*isBanned)));
    }
    if (roles)
    {
        params.insert(make_pair("roles", role));
    }
    auto res = cli.Get(DISPATCHER_GET_BY_ID_MAPPING, params, headers);
    if (res->status == 200)
    {
        json dispatcher_json = json::parse(res->body);
        list<DispatcherModel> result;
        for (auto item : dispatcher_json)
        {
            set<RoleModel> Roles;
            for (auto Role : item["roles"])
            {
                if (Role == "ADMIN")
                {
                    Roles.insert(RoleModel::ADMIN);
                } else if (Role == "DISPATCHER")
                {
                    Roles.insert(RoleModel::DISPATCHER);
                }
            }
            DispatcherModel dispatcher(item["id"], item["firstName"], item["lastName"], item["email"], item["password"], item["isBanned"], Roles);
            result.push_back(dispatcher);
        }
        return result;
    }
    if (res->status == 400)
    {
        throw string("400");
    }
    throw string("500");
}
bool DispatcherRepository::updateDispatchers(DispatcherModel dispatcher, set<string> updates)
{
    Client cli(SERVER_HOST, DATABASE_SERVICE_PORT);

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
        {
            update = item;
        } else
        {
            update += "," + item;
        }
    }
    auto res = cli.Post(DISPATCHER_UPDATE_MAPPING + "?update" + update, headers, dispatcher_json.dump(), "application/json");
    if (res->status == 200)
    {
        return true;
    }
    if (res->status == 400)
    {
        throw string("400");
    }
    throw string("500");
}

