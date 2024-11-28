#include <fstream>
#include "../../header/repos/TimeRepository.h"
#include "../../Config.h"

using namespace std;

long int TimeRepository::getAddedTime()
{
    ifstream file(TIME_FILE_PATH);
    string addedTime;
    if (getline(file, addedTime))
        return stol(addedTime);
    return 0;
}

bool TimeRepository::AddTime(long int addedTime)
{
    long int newAddedTime = getAddedTime() + addedTime;
    ofstream file(TIME_FILE_PATH, ios::trunc);
    file << newAddedTime << endl;
    return true;
}