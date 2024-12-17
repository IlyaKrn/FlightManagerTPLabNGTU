#include "../../header/presentation/IdentityPresenter.h"
#include <iostream>
#include "../../header/repos/TokenRepository.h" // Include TokenRepository header

using namespace std;

bool IdentityPresenter::login() {
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
        *_output << "User   ID: " << userId << endl;
        *_output << "Token: " << token << endl;

        // Сохраняем токен и ID пользователя для дальнейшего использования
        TokenRepository tokenRepo;
        if (tokenRepo.setTokenAndUserId(token, stol(userId))) {
            *_output << "Token and User ID saved successfully." << endl;
            return true; // Успешный вход
        } else {
            *_output << "Failed to save token and User ID." << endl;
            return false; // Неудачный вход
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
        return false; // Неудачный вход
    }
}

bool IdentityPresenter::registerDispatcher() {
    string firstName, lastName, email, password;

    *_output << "Enter first name: ";
    *_input >> firstName;

    *_output << "Enter last name: ";
    *_input >> lastName;

    *_output << "Enter email: ";
    *_input >> email;

    *_output << "Enter password: ";
    *_input >> password;

    // Создаем объект DispatcherModel
    DispatcherModel newDispatcher(0, firstName, lastName, email, password, false, set<RoleModel>());

    IdentityRepository identityRepo;

    try {
        set<string> registrationInfo = identityRepo.regist(newDispatcher);
        string token = *registrationInfo.begin();
        string userId = *(++registrationInfo.begin());

        *_output << "Registration successful!" << endl;
        *_output << "User ID: " << userId << endl;
        *_output << "Token: " << token << endl;

         //Сохраняем токен и ID пользователя для дальнейшего использования
        TokenRepository tokenRepo;
        if (tokenRepo.setTokenAndUserId(token, stol(userId))) {
            *_output << "Token and User ID saved successfully." << endl;
            return true; // Успешная регистрация
        } else {
            *_output << "Failed to save token and User ID." << endl;
            return false; // Неудачная регистрация
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
        return false; // Неудачная регистрация
    }
}