#include "../../header/repos/IdentityRepository.h"
#include "../../Config.h"
#include <cpp-httplib/httplib.h>
#include <json/single_include/nlohmann/json.hpp>

using namespace std;
using namespace httplib;
using namespace nlohmann;
int IdentityRepository::getIdByToken(string token)
{
    Client cli(SERVER_HOST, IDENTITY_SERVICE_PORT);

    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };

    auto res = cli.Post(GET_ID_BY_TOKEN_MAPPING ,headers, token,  "application/json");
    if (res->status == 200)
    {
        int id = stoi(res->body);
        return id;
    }
    if (res->status == 400)
    {
        throw string("400");
    }
    if (res->status == 401)
    {
        throw string("401");
    }
    throw string("500");
}

bool IdentityRepository::authorize(set<string> permissions, string token)
{
    Client cli(SERVER_HOST, IDENTITY_SERVICE_PORT);

    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    json authorize;
    authorize["permissions"] = json::array();
    for (auto permission : permissions)
    {
        authorize["permissions"].push_back(permission);
    }
    authorize["token"] = token;
    auto res = cli.Post(AUTHORIZE_MAPPING, headers, authorize.dump(), "application/json");
    if (res->status == 200)
    {
        if (res->body == "true")
        {
            return true;
        }
        if (res->body == "false")
        {
            return false;
        }
    }
    if (res->status == 400)
    {
        throw string("400");
    }
    throw string("500");
}

