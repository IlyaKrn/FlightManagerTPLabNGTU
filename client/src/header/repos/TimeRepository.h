#pragma once
#include <list>
#include <set>
#include <string>

class TimeRepository
{
public:
    long int getCurrentTime(std::string token);
    bool addTime(long int time, std::string token);
};