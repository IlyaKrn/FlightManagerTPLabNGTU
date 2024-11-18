#pragma once
#include "../repos/TimeRepository.h"
#include "../repos/IdentityRepository.h"

class TimeService
{
    TimeRepository repo;
    IdentityRepository ident;
public:
    long int getCurrentTime();
    void skipTime(long int addedTime);
};
