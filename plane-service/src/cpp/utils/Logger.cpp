#include "../../header/utils/Logger.h"

#include <iostream>

using namespace std;
void Logger::info(std::string inf)
{
    cout << inf << endl;
}

void Logger::warn(std::string warn)
{
    cout << warn << endl;
}
void Logger::error(std::string err)
{
    cout << err << endl;
}
void Logger::debug(std::string debug)
{
    cout << debug << endl;
}