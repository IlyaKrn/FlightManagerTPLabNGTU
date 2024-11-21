#include "../../header/services/DispatcherService.h"

using namespace std;

list<DispatcherModel> DispatcherService::getAllDispatchers(string token)
{
    set<string> permissions;
    list<DispatcherModel> dispatchers = repo.getDispatchers();
    if (dispatchers.empty())
        permissions.insert("dispather-get-public-none");
    else
        permissions.insert("dispather-get-public-all");
    if (!ident.authorize(permissions, token))
         throw 401;
    return dispatchers;
}

DispatcherModel DispatcherService::getDispatcherById(long int id, string token, bool isPrivate)
{
    set<string> permissions;
    if(isPrivate)
        permissions.insert("dispather-get-private " + id);
    else
        permissions.insert("dispather-get-public " + id);

    list<DispatcherModel> dispatchers = repo.getDispatchers(&id);
    if (!ident.authorize(permissions, token))
         throw 401;
    return dispatchers.front();
}

bool DispatcherService::updateDispatcher(DispatcherModel dispatcher, set<string> update, string token)
{
    set<string> permissions;
    if(update.count("password"))
        permissions.insert("dispather-update-private " + dispatcher.getId());
    else
        permissions.insert("dispather-update-public " + dispatcher.getId());

    if (!ident.authorize(permissions, token))
         throw 401;
    long int dispId = dispatcher.getId();
    list<DispatcherModel> n_dispatcher = repo.getDispatchers(&dispId);
    if (update.count("firstName") > 0)
        n_dispatcher.front().setFirstname(dispatcher.getFirstname());
    if (update.count("lastName") > 0)
        n_dispatcher.front().setLastname(dispatcher.getLastname());
    if (update.count("email") > 0)
        n_dispatcher.front().setEmail(dispatcher.getEmail());
    if (update.count("password") > 0)
        n_dispatcher.front().setPassword(dispatcher.getPassword());
    if (update.count("isBanned") > 0)
        n_dispatcher.front().setIsBanned(dispatcher.getIsBanned());
    if (update.count("roles") > 0)
        n_dispatcher.front().setRoles(dispatcher.getRoles());
    bool res = repo.updateDispatchers(n_dispatcher.front(), update);
    return res;
}
