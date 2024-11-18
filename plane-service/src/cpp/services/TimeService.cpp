#include "../../header/services/TimeService.h"
#include <chrono>
#include <ctime>

long int TimeService::getCurrentTime()
{
    return static_cast<long int>(time(nullptr)) + repo.getAddedTime();
}
void TimeService::skipTime(long int addedTime)
{
    repo.AddTime(addedTime);
}

