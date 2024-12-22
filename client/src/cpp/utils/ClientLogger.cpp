#include "../../include/utils/ClientLogger.h"

#include <iostream>

using namespace std;
void ClientLogger::info(std::string inf)
{
    cout << "INFO: " + inf << endl;
}

void ClientLogger::warn(std::string warn)
{
    cout << "WARN: " + warn << endl;
}
void ClientLogger::error(std::string err)
{
    cout << "ERROR: " + err << endl;
}
void ClientLogger::debug(std::string debug)
{
    cout << "DEBUG: " + debug << endl;
}
