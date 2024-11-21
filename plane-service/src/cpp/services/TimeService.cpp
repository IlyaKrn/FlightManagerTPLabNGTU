#include "../../header/services/TimeService.h"
#include <chrono>
#include <ctime>
using namespace std;
long int TimeService::getCurrentTime(string token)
{
    set<string> permissions;
    permissions.insert("time-get");
    bool isAllowed = ident.authorize(permissions, token);
    if (!isAllowed)
        throw 401;
    return static_cast<long int>(time(nullptr)) + repo.getAddedTime();
}
void TimeService::skipTime(long int addedTime, string token)
{
    set<string> permissions;
    permissions.insert("time-skip");
    bool isAllowed = ident.authorize(permissions, token);
    if (!isAllowed)
        throw 401;
    repo.AddTime(addedTime);
}

