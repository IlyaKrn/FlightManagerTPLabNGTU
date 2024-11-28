#include "../../header/presentation/IdentityPresenter.h"
#include <iostream>

using namespace std;

void IdentityPresenter::login() {
    string email, password;

    *_output << "Enter your email: ";
    *_input >> email;

    *_output << "Enter your password: ";
    *_input >> password;

    IdentityRepository identityRepo;

    try {
        set<string> loginInfo = identityRepo.login(email, password);
        // Предполагаем, что получаем id и token
        string userId = *loginInfo.begin();
        string token = *(++loginInfo.begin());

        *_output << "Login successful!" << endl;
        *_output << "User  ID: " << userId << endl;
        *_output << "Token: " << token << endl;

        //хранилище для токена
    } catch (const int& status) {
        *_output << "Login failed with status: " << status << endl;
    }
}

void IdentityPresenter::registerDispatcher() {
    long int id;
    string firstName, lastName, email, password;
    bool isBanned;

    *_output << "Enter dispatcher ID: ";
    *_input >> id;

    *_output << "Enter first name: ";
    *_input >> firstName;

    *_output << "Enter last name: ";
    *_input >> lastName;

    *_output << "Enter email: ";
    *_input >> email;

    *_output << "Enter password: ";
    *_input >> password;

    *_output << "Is banned (1 for Yes, 0 for No): ";
    int bannedInput;
    *_input >> bannedInput;
    isBanned = (bannedInput == 1);

    // Создаем объект DispatcherModel
    DispatcherModel newDispatcher(id, firstName, lastName, email, password, isBanned, set<RoleModel>());

    IdentityRepository identityRepo;

    try {
        set<string> registrationInfo = identityRepo.regist(newDispatcher);
        string userId = *registrationInfo.begin();
        string token = *(++registrationInfo.begin());

        *_output << "Registration successful!" << endl;
        *_output << "User  ID: " << userId << endl;
        *_output << "Token: " << token << endl;

        //хранилище для токена
    } catch (const int& status) {
        *_output << "Registration failed with status: " << status << endl;
    }
}