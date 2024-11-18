#pragma once
#include "../models/TimeModel.h"

class TimeService
{
    TimeModel timer;
public:
    long int getCurrentTime();
    void skipTime(long int addedTime);
};
