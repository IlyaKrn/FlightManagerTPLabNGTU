#include "../../header/models/DispatcherModel.h"
DispatcherModel::DispatcherModel(int id, std::string name, std::string firstname, std::string lastname, std::string email, std::string password, bool isBanned, std::set<RoleModel> roles)
{
    _id = id;
    _name = name;
    _firstname = firstname;
    _lastname = lastname;
    _email = email;
    _password = password;
    _isBanned = isBanned;
    _roles = roles;
}

int DispatcherModel::getId()
{
    return _id;
}
std::string DispatcherModel::getName()
{
    return _name;
}
std::string DispatcherModel::getFirstname()
{
    return _firstname;
}
std::string DispatcherModel::getLastname()
{
    return _lastname;
}
std::string DispatcherModel::getEmail()
{
    return _email;
}
std::string DispatcherModel::getPassword()
{
    return _password;
}
bool DispatcherModel::getIsBanned()
{
    return _isBanned;
}
std::set<RoleModel> DispatcherModel::getRoles()
{
    return _roles;
}


void DispatcherModel::setId(int id)
{
    _id = id;
}
void DispatcherModel::setName(std::string name)
{
    _name = name;
}
void DispatcherModel::setFirstname(std::string firstname)
{
    _firstname = firstname;
}
void DispatcherModel::setLastname(std::string lastname)
{
    _lastname = lastname;
}
void DispatcherModel::setEmail(std::string email)
{
    _email = email;
}
void DispatcherModel::setPassword(std::string password)
{
    _password = password;
}
void DispatcherModel::setIsBanned(bool isBanned)
{
    _isBanned = isBanned;
}
void DispatcherModel::setRoles(std::set<RoleModel> roles)
{
    _roles = roles;
}


