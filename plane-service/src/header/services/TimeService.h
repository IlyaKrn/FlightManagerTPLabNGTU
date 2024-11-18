#pragma once
#include "../models/TimeModel.h"

class TimeService
{
public:
    long int getCurrentTime();
    void skipTime(long int addedTime);
};
