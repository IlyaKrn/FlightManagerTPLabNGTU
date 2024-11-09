#pragma once
#include <list>
#include <string>
#include "../repos/DispatcherRepository.h"
#include "../repos/IdentityRepository.h"
class DispatcherService
{
private:
    DispatcherRepository repo;
    IdentityRepository ident;
public:
    std::pmr::list<DispatcherModel> getAllDispatchers(std::string token, std::set<std::string> permissions);
    DispatcherModel getDispatcherById(int id, std::string token, std::set<std::string> permissions);
    bool editDispatcher(DispatcherModel dispatcher, std::string update, std::string token, std::set<std::string> permissions);
};