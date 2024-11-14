#include "../../header/repos/PlaneRepository.h"
#include "../../Config.h"
#include <cpp-httplib/httplib.h>
#include <json/single_include/nlohmann/json.hpp>

using namespace std;
using namespace httplib;
using namespace nlohmann;
list<PlaneModel> PlaneRepository::getPlanes(long int* id, string* name, string* pilot, int* builtYear, int* brokenPercentage, int* speed, int* minAirportSize)
{
    Client cli(SERVER_HOST, DATABASE_SERVICE_PORT);

    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    Params params = {
        {"id", to_string(*id) },
        {"name", *name},
        {"pilot", *pilot},
        {"builtYear", to_string(*builtYear)},
        {"brokenPercentage", to_string(*brokenPercentage)},
        {"speed", to_string(*speed)},
        {"minAirportSize", to_string(*minAirportSize)}
    };
    auto res = cli.Get(PLANE_GET_BY_ID_MAPPING, params, headers);
    if (res->status == 200)
    {
        json planes = json::parse(res->body);
        list<PlaneModel> result;
        for (auto item: planes)
        {
            PlaneModel plane(item["id"], item["name"],item["pilot"], item["builtYear"], item["brokenPercentage"],item["speed"], item["minAirportSize"]);
            result.push_back(plane);
        }
        return result;
    }
    if (res->status == 400)
    {
        throw string("400");
    }
    throw string("500");
}
bool PlaneRepository::createPlane(PlaneModel plane)
{
    Client cli(SERVER_HOST, DATABASE_SERVICE_PORT);

    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    json plane_json;
    plane_json["id"] = plane.getId();
    plane_json["name"] = plane.getName();
    plane_json["pilot"] = plane.getPilot();
    plane_json["builtYear"] = plane.getBuiltYear();
    plane_json["brokenPercentage"] = plane.getBrokenPercentage();
    plane_json["speed"] = plane.getSpeed();
    plane_json["minAirportSize"] = plane.getMinAirportSize();

    auto res = cli.Post(PLANE_CREATE_MAPPING, headers, plane_json.dump(), "application/json");
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
bool PlaneRepository::deletePlane(long int id)
{
    Client cli(SERVER_HOST, DATABASE_SERVICE_PORT);

    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };

    auto res = cli.Delete(PLANE_DELETE_MAPPING + "/" + to_string(id), headers);
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
bool PlaneRepository::updatePlane(PlaneModel plane, set<string> updates)
{
    Client cli(SERVER_HOST, DATABASE_SERVICE_PORT);

    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    json plane_json;
    plane_json["id"] = plane.getId();
    plane_json["name"] = plane.getName();
    plane_json["pilot"] = plane.getPilot();
    plane_json["builtYear"] = plane.getBuiltYear();
    plane_json["brokenPercentage"] = plane.getBrokenPercentage();
    plane_json["speed"] = plane.getSpeed();
    plane_json["minAirportSize"] = plane.getMinAirportSize();
    string update;
    for (auto item: update)
    {
        if (update.empty())
        {
            update = item;
        } else
        {
            update += "," + item;
        }
    }
    auto res = cli.Post(PLANE_UPDATE_MAPPING + "?update=" + update, headers, plane_json.dump(), "application/json");
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

