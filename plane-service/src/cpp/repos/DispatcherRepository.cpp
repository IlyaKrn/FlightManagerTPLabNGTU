#include "../../header/repos/DispatcherRepository.h"
#include "../../header/Config.h"
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
            DispatcherModel dispatcher(item["id"], item["name"], item["firstname"], item["lastname"], item["emal"], item["password"], item["isBanned"], item["roles"]);
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
    dispatcher_json["name"] = dispatcher.getName();
    dispatcher_json["firstname"] = dispatcher.getFirstname();
    dispatcher_json["lastname"] = dispatcher.getLastname();
    dispatcher_json["email"] = dispatcher.getEmail();
    dispatcher_json["password"] = dispatcher.getPassword();
    dispatcher_json["isBanned"] = dispatcher.getIsBanned();
    dispatcher_json["roles"] = dispatcher.getRoles();
    auto res = cli.Post(DISPATCHER_UPDATE_MAPPING + "?update" + update, headers, dispatcher_json.dump(), "application/json");
    if (res->status == 200)
    {
        return true;
    }
    return false;
}

