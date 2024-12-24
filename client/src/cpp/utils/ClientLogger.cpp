#include "../../include/utils/ClientLogger.h"
#include "../../include/Config.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace src;
void ClientLogger::info(std::string inf)
{
    if (logsEnable && isConsole)
        cout << "INFO: " + inf << endl;
    if (logsEnable && isFile){
        ofstream file(LOGS_FILE_PATH);
        file << "INFO: " + inf << endl;
        file.close();
    }
    if (!logsEnable)
        return;
}

void ClientLogger::warn(std::string warn)
{
    if (logsEnable && isConsole)
        cout << "WARN: " + warn << endl;
    if (logsEnable && isFile){
        ofstream file(LOGS_FILE_PATH);
        file << "WARN: " + warn << endl;
        file.close();
    }
    if (!logsEnable)
        return;
}
void ClientLogger::error(std::string err)
{
    if (logsEnable && isConsole)
        cout << "ERROR: " + err << endl;
    if (logsEnable && isFile){
        ofstream file(LOGS_FILE_PATH);
        file << "ERROR: " + err << endl;
        file.close();
    }
    if (!logsEnable)
        return;
}
void ClientLogger::debug(std::string debug)
{
    if (logsEnable && isConsole)
        cout << "DEBUG: " + debug << endl;
    if (logsEnable && isFile){
        ofstream file(LOGS_FILE_PATH);
        file << "DEBUG: " + debug << endl;
        file.close();
    }
    if (!logsEnable)
        return;
}
