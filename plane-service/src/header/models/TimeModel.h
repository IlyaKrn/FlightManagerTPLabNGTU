#pragma once

class TimeModel
{
    long int _currentTime;
    long int _addedTime;
public:
    TimeModel(long int currentTime, long int addedTime);

    long int getCurrentTime();
    long int getAddedTime();

    void setCurrentTime(long int currentTime);
    void setAddedTime(long int addedTime);
};
