#pragma once
#include <list>
#include <set>
#include <string>
#include "../../header/models/DispatcherModel.h"

class IdentityRepository
{
public:
    std::set<std::string> login(std::string email, std::string password);
    std::set<std::string> Register(DispatcherModel dispatcher);
};
