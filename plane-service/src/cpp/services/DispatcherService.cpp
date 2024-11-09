#include "../../header/services/DispatcherService.h"

std::pmr::list<DispatcherModel> DispatcherService::getAllDispatchers()
{
    std::pmr::list<DispatcherModel> dispatchers = repo.getDispatchers("");
    if (!dispatchers.empty())
    {
        return dispatchers;
    }
    return std::pmr::list<DispatcherModel>();
}
DispatcherModel DispatcherService::getDispatcherById(int id)
{
    std::pmr::list<DispatcherModel> dispatchers = repo.getDispatchers(std::to_string(id));
    DispatcherModel empty_dispatcher;
    for (auto dispatcher : dispatchers)
    {
        if (dispatcher.getId() != empty_dispatcher.getId())
        {
            return dispatcher;
        }
    }
    return empty_dispatcher;
}
bool DispatcherService::editDispatcher(DispatcherModel dispatcher, std::string update)
{
    DispatcherModel n_dispatcher = getDispatcherById(dispatcher.getId());
    if (update.find("name") != std::string::npos)
    {
        n_dispatcher.setName(dispatcher.getName());
    }
    if (update.find("firstname") != std::string::npos)
    {
        n_dispatcher.setFirstname(dispatcher.getFirstname());
    }
    if (update.find("lastname") != std::string::npos)
    {
        n_dispatcher.setLastname(dispatcher.getLastname());
    }
    if (update.find("email") != std::string::npos)
    {
        n_dispatcher.setEmail(dispatcher.getEmail());
    }
    if (update.find("password") != std::string::npos)
    {
        n_dispatcher.setPassword(dispatcher.getPassword());
    }
    if (update.find("isBanned") != std::string::npos)
    {
        n_dispatcher.setIsBanned(dispatcher.getIsBanned());
    }
    if (update.find("roles") != std::string::npos)
    {
        n_dispatcher.setRoles(dispatcher.getRoles());
    }
    bool res = repo.updateDispatchers(n_dispatcher, update);
    if (res)
    {
        return true;
    }
    return false;
}
