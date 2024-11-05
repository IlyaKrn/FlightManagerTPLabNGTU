#pragma once
#include <list>
#include <string>
#include "../models/DispatcherModel.h"
#include <json/single_include/nlohmann/json.hpp>

class DispatcherRepository
{
public:
    std::pmr::list<DispatcherModel> getDispatchers(std::string id);
    bool updateDispatchers(DispatcherModel dispatcher, std::string update);
};
