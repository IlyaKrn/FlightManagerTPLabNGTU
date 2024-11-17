#include "../../header/models/TimeModel.h"

TimeModel::TimeModel()
{
    _currentTime = 0;
    _addedTime = 0;
}
long int TimeModel::getAddedTime()
{
    return _addedTime;
}
long int TimeModel::getCurrentTime()
{
    return _currentTime;
}

void TimeModel::setCurrentTime(long int currentTime)
{
    _currentTime = currentTime;
}
void TimeModel::setAddedTime(long int addedTime)
{
    _addedTime = addedTime;
}

