#pragma once
#include <list>
#include <set>
#include <string>
#include "../repos/DispatcherRepository.h"
#include "../repos/IdentityRepository.h"

class DispatcherService
{
    DispatcherRepository repo;
    IdentityRepository ident;
public:
    std::list<DispatcherModel> getAllDispatchers(std::string token, std::set<std::string> permissions);
    DispatcherModel getDispatcherById(long int id, std::string token, std::set<std::string> permissions);
    bool editDispatcher(DispatcherModel dispatcher, std::set<std::string> update, std::string token, std::set<std::string> permissions);
};