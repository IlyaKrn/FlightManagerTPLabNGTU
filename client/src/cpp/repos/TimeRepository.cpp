#include "../../header/repos/TimeRepository.h"

#include <cpp-httplib/httplib.h>
#include <json/single_include/nlohmann/json.hpp>

#include "../../Config.h"
using namespace std;
using namespace httplib;
using namespace nlohmann;

long int TimeRepository::getCurrentTime(string token) {
    Client cli(GATEWAY_HOST_PORT);

    Headers headers = {
        { AUTH_TOKEN_NAME, token }
    };
    auto res = cli.Get(TIME_GET_MAPPING, headers);
    if (res->status >= 200 && res->status < 300) {
        try {
            long int time = stol(res->body);
            return time;
        } catch (...)
        {
            throw 500;
        }
    }

    throw res->status;
}

bool TimeRepository::addTime(long int time, string token) {
    Client cli(GATEWAY_HOST_PORT);
    Headers headers = {
        { AUTH_TOKEN_NAME, token }
    };

    auto res = cli.Post(TIME_SKIP_MAPPING + "?skip=" + to_string(time), headers);
    if (res->status >= 200 && res->status < 300)
        return true;
    throw res->status;
}