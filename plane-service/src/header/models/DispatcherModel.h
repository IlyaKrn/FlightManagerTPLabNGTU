#pragma once

#include <string>
#include <set>
#include "RoleModel.h"
class DispatcherModel
{
private:
    int _id = 0;
    std::string _name;
    std::string _firstname;
    std::string _lastname;
    std::string _email;
    std::string _password;
    bool _isBanned;
    std::set<RoleModel> _roles;
public:
    DispatcherModel(int id, std::string name, std::string firstname, std::string lastname, std::string email, std::string password, bool isBanned, std::set<RoleModel> roles);
    DispatcherModel() = default;

    int getId();
    std::string getName();
    std::string getFirstname();
    std::string getLastname();
    std::string getEmail();
    std::string getPassword();
    bool getIsBanned();
    std::set<RoleModel> getRoles();

    void setId(int id);
    void setName(std::string name);
    void setFirstname(std::string firstname);
    void setLastname(std::string lastname);
    void setEmail(std::string email);
    void setPassword(std::string password);
    void setIsBanned(bool isBanned);
    void setRoles(std::set<RoleModel> roles);

};