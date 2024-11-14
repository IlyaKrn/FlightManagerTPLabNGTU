#include "../../header/repos/AirportRepository.h"
#include "../../Config.h"
#include <cpp-httplib/httplib.h>
#include <json/single_include/nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;
using namespace httplib;
list<AirportModel> AirportRepository::getAirports(long int* id, string* name, int* size, double* x, double* y)
{

    Client cli(SERVER_HOST, DATABASE_SERVICE_PORT);

    Headers headers = {
        {SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE}
    };
    Params params = {
        {"id", to_string(*id)},
        {"name", *name},
        {"size", to_string(*size)},
        {"x", to_string(*x)},
        {"y", to_string(*y)}
    };
    auto res = cli.Get(AIRPORT_GET_BY_ID_MAPPING, params, headers);
    if (res->status == 200)
    {
        json airports = json::parse(res->body);
        list<AirportModel> result;
        for (auto& item : airports)
        {
            AirportModel airport(item["id"], item["name"], item["size"], item["x"], item["y"]);
            result.push_back(airport);
        }
        return result;
    }
    if (res->status == 400)
    {
        throw string("400");
    }
    throw string("500");
}
bool AirportRepository::createAirport(AirportModel airport)
{
    Client cli(SERVER_HOST, DATABASE_SERVICE_PORT);

    Headers headers = {
            { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    json airport_json;
    airport_json["id"] = airport.getId();
    airport_json["name"] = airport.getName();
    airport_json["size"] = airport.getSize();
    airport_json["x"] = airport.getX();
    airport_json["y"] = airport.getY();

    auto res = cli.Post(AIRPORT_CREATE_MAPPING, headers, airport_json.dump(), "application/json");
    if (res->status == 200){
        return true;
    }
    if (res->status == 400)
    {
        throw string("400");
    }
    throw string("500");
}
bool AirportRepository::updateAirport(AirportModel airport, set<string> updates)
{
    Client cli(SERVER_HOST, DATABASE_SERVICE_PORT);

    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };

    json airport_json;
    airport_json["id"] = airport.getId();
    airport_json["name"] = airport.getName();
    airport_json["size"] = airport.getSize();
    airport_json["x"] = airport.getX();
    airport_json["y"] = airport.getY();
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
    auto res = cli.Post((AIRPORT_UPDATE_MAPPING + "?update=" + update), headers, airport_json.dump(), "application/json");
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


bool AirportRepository::deleteAirport(long int id)
{
    Client cli(SERVER_HOST, DATABASE_SERVICE_PORT);

    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    auto res = cli.Delete(AIRPORT_DELETE_MAPPING + "/" + to_string(id), headers);
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
