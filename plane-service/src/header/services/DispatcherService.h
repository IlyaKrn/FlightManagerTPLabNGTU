#pragma once
#include <list>
#include <string>
#include "../repos/DispatcherRepository.h"
class DispatcherService
{
private:
    DispatcherRepository repo;
public:
    std::pmr::list<DispatcherModel> getAllDispatchers();
    DispatcherModel getDispatcherById(int id);
    bool editDispatcher(DispatcherModel dispatcher, std::string update);
};