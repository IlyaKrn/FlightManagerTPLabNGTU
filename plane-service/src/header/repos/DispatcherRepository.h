#pragma once
#include <list>
#include <string>
#include "../models/DispatcherModel.h"

class DispatcherRepository
{
public:
    std::pmr::list<std::string> getDispatchers();
    bool updateDispatchers(DispatcherRepository dispatcher);
};
