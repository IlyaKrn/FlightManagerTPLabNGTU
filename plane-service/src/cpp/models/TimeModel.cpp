#include "../../header/models/TimeModel.h"


TimeModel::TimeModel(long int currentTime, long int addedTime)
{
    _currentTime = currentTime;
    _addedTime = addedTime;
}

long int TimeModel::getCurrentTime()
{
    return _currentTime;
}

long int TimeModel::getAddedTime()
{
    return _addedTime;
}

void TimeModel::setCurrentTime(long int currentTime)
{
    _currentTime = currentTime;
}

void TimeModel::setAddedTime(long int addedTime)
{
    _addedTime = addedTime;
}
