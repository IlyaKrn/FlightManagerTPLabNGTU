#include "../../header/services/TimeService.h"
#include <chrono>
#include <ctime>

long int TimeService::getCurrentTime()
{
    timer.setCurrentTime(time(0));
    return timer.getCurrentTime() + timer.getAddedTime();
}
void TimeService::skipTime(long int addedTime)
{
    timer.setAddedTime(addedTime);
}

