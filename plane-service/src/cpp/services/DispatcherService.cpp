#include "../../header/services/DispatcherService.h"

using namespace std;

list<DispatcherModel> DispatcherService::getAllDispatchers(string token)
{
    set<string> permissions;
    permissions.insert("public"); //оставить
    bool isAllowed = ident.authorize(permissions, token);
    if (!isAllowed)
        throw 401;
    list<DispatcherModel> dispatchers = repo.getDispatchers();
    return dispatchers;
}

DispatcherModel DispatcherService::getDispatcherById(long int id, string token, bool isPrivate)
{
    set<string> permissions;
    if(isPrivate)
        permissions.insert("dispather-get private " + id);
    else
        permissions.insert("dispather-get public " + id);

    list<DispatcherModel> dispatchers = repo.getDispatchers(&id);
    bool isAllowed = ident.authorize(permissions, token);
    if (!isAllowed)
        throw 401;
    return dispatchers.front();
}

bool DispatcherService::updateDispatcher(DispatcherModel dispatcher, set<string> update, string token)
{
    set<string> permissions;
    if(update.count("password"))
        permissions.insert("dispather-get private " + dispatcher.getId());
    else
        permissions.insert("dispather-get public " + dispatcher.getId());

    bool isAllowed = ident.authorize(permissions, token);
    if (!isAllowed)
        throw 401;
    DispatcherModel n_dispatcher = getDispatcherById(dispatcher.getId(), token);
    if (update.count("firstName") > 0)
        n_dispatcher.setFirstname(dispatcher.getFirstname());
    if (update.count("lastName") > 0)
        n_dispatcher.setLastname(dispatcher.getLastname());
    if (update.count("email") > 0)
        n_dispatcher.setEmail(dispatcher.getEmail());
    if (update.count("password") > 0)
        n_dispatcher.setPassword(dispatcher.getPassword());
    if (update.count("isBanned") > 0)
        n_dispatcher.setIsBanned(dispatcher.getIsBanned());
    if (update.count("roles") > 0)
        n_dispatcher.setRoles(dispatcher.getRoles());
    bool res = repo.updateDispatchers(n_dispatcher, update);
    return res;
}
