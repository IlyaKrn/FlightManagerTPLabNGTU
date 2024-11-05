#include "../../header/repos/AirportRepository.h"


std::pmr::list<std::string> AirportRepository::getAirports()
{
    httplib::Client cli(DATABASE_SERVICE_HOST, DATABASE_SERVICE_PORT);

    httplib::Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };

    auto res = cli.Get(DATABASE_SERVICE_GET_AIRPORTS, headers);
    if (res->status == 200)
    {
        nlohmann::json airports = nlohmann::json::parse(res->body);
        std::pmr::list<std::string> result;
        for (const auto& airport : airports)
        {
            nlohmann::json airport_json = nlohmann::json::parse(airport.dump());
            result.push_back(airport_json.dump());
        }
        return result;

    }
    throw std::string("AirportRepository::getAirports() failed");

}
