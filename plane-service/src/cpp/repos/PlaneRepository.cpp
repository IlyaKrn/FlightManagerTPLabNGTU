#include "../../header/repos/PlaneRepository.h"
#include "../../header/Config.h"
#include <cpp-httplib/httplib.h>
#include <json/single_include/nlohmann/json.hpp>

std::pmr::list<PlaneModel> PlaneRepository::getPlanes(std::string id)
{
    httplib::Client cli(DATABASE_SERVICE_HOST, DATABASE_SERVICE_PORT);

    httplib::Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    httplib::Params params = {
        {"id", id }
    };
    auto res = cli.Get(PLANE_GET_BY_ID_MAPPING, params, headers);
    if (res->status == 200)
    {
        nlohmann::json planes = nlohmann::json::parse(res->body);
        std::pmr::list<PlaneModel> result;
        for (auto item: planes)
        {
            PlaneModel plane(item["id"], item["name"],item["pilot"], item["builtYear"], item["brokenPercentage"],item["speed"], item["minAirportSize"]);
            result.push_back(plane);
        }
        return result;
    }
    return std::pmr::list<PlaneModel>();
}
bool PlaneRepository::createPlane(PlaneModel plane)
{
    httplib::Client cli(DATABASE_SERVICE_HOST, DATABASE_SERVICE_PORT);

    httplib::Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    nlohmann::json plane_json;
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
    return false;
}
bool PlaneRepository::deletePlane(int id)
{
    httplib::Client cli(DATABASE_SERVICE_HOST, DATABASE_SERVICE_PORT);

    httplib::Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };

    auto res = cli.Delete(PLANE_DELETE_MAPPING + "/" + std::to_string(id), headers);
    if (res->status == 200)
    {
        return true;
    }
    return false;
}
bool PlaneRepository::updatePlane(PlaneModel plane, std::string update)
{
    httplib::Client cli(DATABASE_SERVICE_HOST, DATABASE_SERVICE_PORT);

    httplib::Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    nlohmann::json plane_json;
    plane_json["id"] = plane.getId();
    plane_json["name"] = plane.getName();
    plane_json["pilot"] = plane.getPilot();
    plane_json["builtYear"] = plane.getBuiltYear();
    plane_json["brokenPercentage"] = plane.getBrokenPercentage();
    plane_json["speed"] = plane.getSpeed();
    plane_json["minAirportSize"] = plane.getMinAirportSize();

    auto res = cli.Post(PLANE_UPDATE_MAPPING + "?update=" + update, headers, plane_json.dump(), "application/json");
    if (res->status == 200)
    {
        return true;
    }
    return false;
}

