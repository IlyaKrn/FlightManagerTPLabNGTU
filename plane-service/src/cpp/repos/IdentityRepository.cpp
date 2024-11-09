#include "../../header/repos/IdentityRepository.h"
#include "../../Config.h"
#include <cpp-httplib/httplib.h>
#include <json/single_include/nlohmann/json.hpp>

int IdentityRepository::getIdByToken(std::string token)
{
    httplib::Client cli(DATABASE_SERVICE_HOST, IDENTITY_SERVICE_PORT);

    httplib::Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };

    auto res = cli.Post(GET_ID_BY_TOKEN_MAPPING ,headers, token,  "application/json");
    if (res->status == 200)
    {
        int id = std::stoi(res->body);
        return id;
    }
    return 0;
}

bool IdentityRepository::authorize(std::set<std::string> permissions, std::string token)
{
    httplib::Client cli(DATABASE_SERVICE_HOST, IDENTITY_SERVICE_PORT);

    httplib::Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    nlohmann::json authorize;
    authorize["permissions"] = nlohmann::json::array();
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
    }
    return false;
}

