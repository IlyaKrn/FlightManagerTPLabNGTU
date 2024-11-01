#pragma once
#include <list>
#include <string>
#include "../repos/DispatcherRepository.h"
class DispatcherService
{
private:
    DispatcherRepository repo;
public:
    std::list<std::string> getAllDispatchers();
    std::string getDispatcherById(int id);
    bool editDispatcher(DispatcherModel dispatcher);
};