//
// Created by IlyaKrn on 19.11.2024.
//
#include <fstream>
#include "../../header/repos/TimeRepository.h"

#include <ctime>
using namespace std;
long int TimeRepository::getAddedTime()
{
    ifstream file("time.txt");
    string addedTime;
    if (getline(file, addedTime))
        return stol(addedTime);
    return 0;
}

bool TimeRepository::AddTime(long int addedTime)
{
    ofstream file("time.txt");
    file << addedTime << endl;
    return true;
}
