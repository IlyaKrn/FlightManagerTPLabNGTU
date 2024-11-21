#include "../../header/repos/TimeRepository.h"

#include <cpp-httplib/httplib.h>
#include <json/single_include/nlohmann/json.hpp>

#include "../../Config.h"
using namespace std;
using namespace httplib;
using namespace nlohmann;

long int TimeRepository::getCurrentTime(string token) {
    Client cli(GATEWAY_HOST, GATEWAY_PORT);

    Headers headers = {
        { AUTH_TOKEN_NAME, token }
    };
    auto res = cli.Get(TIME_GET_MAPPING, headers);
    if (res->status >= 200 && res->status < 300) {
        json zalupka = json::parse(res->body);
        long int time = zalupka["time"];
        return time;
    }

    throw res->status;
}

bool TimeRepository::addTime(string token, long int time) {
    Client cli(GATEWAY_HOST, GATEWAY_PORT);
    Headers headers = {
        { AUTH_TOKEN_NAME, token }
    };

    Params params = {
        {"skip", to_string(time)}
    };
    auto res = cli.Post(TIME_SKIP_MAPPING, headers, params);
    if (res->status >= 200 && res->status < 300)
        return true;
    throw res->status;
}