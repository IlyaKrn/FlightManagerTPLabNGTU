#include "../../header/presentation/IdentityPresenter.h"
#include <iostream>
#include "../../header/repos/TokenRepository.h" // Include TokenRepository header

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

        // Сохраняем токен и ID пользователя для дальнейшего использования
        TokenRepository tokenRepo;
        if (tokenRepo.setTokenAndUserId(token, stol(userId))) {
            *_output << "Token and User ID saved successfully." << endl;
        } else {
            *_output << "Failed to save token and User ID." << endl;
        }
    } catch (const int& status) {
        // Обработка ошибок
        switch (status) {
            case 500:
                *_output << "Internal server error. Please try again later." << endl;
                break;
            case 400:
                *_output << "Wrong request. Please check your input." << endl;
                break;
            case 403:
                *_output << "Forbidden access. You do not have permission." << endl;
                break;
            case 401:
                *_output << "Unauthorized access. Check your credentials." << endl;
                break;
            default:
                *_output << "An unexpected error occurred. Please contact support." << endl;
                break;
        }
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

        // Сохраняем токен и ID пользователя для дальнейшего использования
        TokenRepository tokenRepo;
        if (tokenRepo.setTokenAndUserId(token, stol(userId))) {
            *_output << "Token and User ID saved successfully." << endl;
        } else {
            *_output << "Failed to save token and User ID." << endl;
        }
    } catch (const int& status) {
        // Обработка ошибок
        switch (status) {
            case 500:
                *_output << "Internal server error. Please try again later." << endl;
                break;
            case 400:
                *_output << "Wrong request. Please check your input." << endl;
                break;
            case 403:
                *_output << "Forbidden access. You do not have permission." << endl;
                break;
            case 409:
                *_output << "Conflict! This dispatcher ID may already exist." << endl;
                break;
            case 401:
                *_output << "Unauthorized access. Check your credentials." << endl;
                break;
            default:
                *_output << "An unexpected error occurred. Please contact support." << endl;
                break;
        }
    }
}