#pragma once
#include <list>
#include <set>
#include <string>
#include "../models/DispatcherModel.h"

class DispatcherRepository
{
public:
    std::list<DispatcherModel> getDispatchers(std::string token);

    bool updateDispatchers(DispatcherModel dispatcher, std::set<std::string> updates, std::string token);

    DispatcherModel getDispatcherByID(std::string token, long int id);
};
