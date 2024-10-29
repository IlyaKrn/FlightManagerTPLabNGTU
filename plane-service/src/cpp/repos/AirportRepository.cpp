//
// Created by IlyaKrn on 29.10.2024.
//

#include "../../header/repos/AirportRepository.h"

#include <cpp-httplib/httplib.h>
#include <json/single_include/nlohmann/json.hpp>
#include "../../header/Config.h"

std::pmr::list<std::string> AirportRepository::getAirports(int param1, std::string param2)
{
    httplib::Client cli(DATABASE_SERVICE_HOST, DATABASE_SERVICE_PORT);

    httplib::Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    httplib::Params params = {
        { "id", "2" }
    };
    auto res = cli.Get(DATABASE_SERVICE_GET_AIRPORTS, params, headers);
    if (res->status == 200)
    {
        nlohmann::json j = nlohmann::json::parse(res->body);
        std::cout << j << std::endl;
      //  auto p2 = j.get<std::pmr::list<std::string>>();
        std::pmr::list<std::string> result = std::pmr::list<std::string>();
        result.push_back(j.dump());
        return result;

    }
    throw std::string("AirportRepository::getAirports() failed");

}
