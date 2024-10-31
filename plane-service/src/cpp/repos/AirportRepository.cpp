//
// Created by IlyaKrn on 29.10.2024.
//

#include "../../header/repos/AirportRepository.h"

#include <cpp-httplib/httplib.h>
#include <json/single_include/nlohmann/json.hpp>
#include "../../Config.h"

std::pmr::list<std::string> AirportRepository::getAirports(int param1, std::string param2)
{
    httplib::Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    httplib::Params params = {
        {"param1", std::to_string(param1)},
        {"param2", param2}
    };
    auto response = httplib::Client(DATABASE_SERVICE_URL).Get(DATABASE_SERVICE_GET_AIRPORTS, params, headers);

    if (response->status >= 200 && response->status < 300)
    {
        return std::pmr::list<std::string>();
    }
    throw std::string("sample error message");

}
