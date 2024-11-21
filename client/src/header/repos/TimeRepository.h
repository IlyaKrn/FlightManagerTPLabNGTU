#pragma once
#include <list>
#include <set>
#include <string>

class TimeRepository
{
public:
    long int getCurrentTime(std::string token);

    bool addTime(std::string token, long int time);
};