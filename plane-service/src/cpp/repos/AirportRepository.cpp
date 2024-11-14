#include "../../header/repos/AirportRepository.h"
#include "../../Config.h"
#include <cpp-httplib/httplib.h>

std::pmr::list<AirportModel> AirportRepository::getAirports(std::string id)
{
    httplib::Client cli(DATABASE_SERVICE_HOST, DATABASE_SERVICE_PORT);

    httplib::Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    httplib::Params params = {
        {"id", id }
    };
    auto res = cli.Get(AIRPORT_GET_BY_ID_MAPPING, params, headers);
    if (res->status == 200)
    {
        nlohmann::json airports = nlohmann::json::parse(res->body);
        std::pmr::list<AirportModel> result;
        for (auto& item : airports)
        {
            AirportModel airport(item["id"], item["name"], item["size"], item["x"], item["y"]);
            result.push_back(airport);
        }
        return result;
    }
    return std::pmr::list<AirportModel>();

}
bool AirportRepository::createAirport(AirportModel airport)
{
    httplib::Client cli(DATABASE_SERVICE_HOST, DATABASE_SERVICE_PORT);

    httplib::Headers headers = {
            { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    nlohmann::json airport_json;
    airport_json["id"] = airport.getId();
    airport_json["name"] = airport.getName();
    airport_json["size"] = airport.getSize();
    airport_json["x"] = airport.getX();
    airport_json["y"] = airport.getY();

    auto res = cli.Post(AIRPORT_CREATE_MAPPING, headers, airport_json.dump(), "application/json");
    if (res->status == 200){
        return true;
    }
    return false;
}
bool AirportRepository::updateAirport(AirportModel airport, std::string update)
{
    httplib::Client cli(DATABASE_SERVICE_HOST, DATABASE_SERVICE_PORT);

    httplib::Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };

    nlohmann::json airport_json;
    airport_json["id"] = airport.getId();
    airport_json["name"] = airport.getName();
    airport_json["size"] = airport.getSize();
    airport_json["x"] = airport.getX();
    airport_json["y"] = airport.getY();

    auto res = cli.Post((AIRPORT_UPDATE_MAPPING + "?update=" + update), headers, airport_json.dump(), "application/json");
    if (res->status == 200)
    {
        return true;
    }
    return false;
}


bool AirportRepository::deleteAirport(int id)
{
    httplib::Client cli(DATABASE_SERVICE_HOST, DATABASE_SERVICE_PORT);

    httplib::Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    auto res = cli.Delete(AIRPORT_DELETE_MAPPING + "/" + std::to_string(id), headers);
    if (res->status == 200)
    {
        return true;
    }
    return false;
}
