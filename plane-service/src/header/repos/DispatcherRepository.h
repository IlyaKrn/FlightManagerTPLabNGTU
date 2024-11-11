#pragma once
#include <list>
#include <set>
#include <string>
#include "../models/DispatcherModel.h"

class DispatcherRepository
{
public:
    std::list<DispatcherModel> getDispatchers(long int id, std::string firstName, std::string lastName, std::string email, std::string password, bool isBanned);
    bool updateDispatchers(DispatcherModel dispatcher, std::set<std::string> update);
};
