#include "../../header/presentation/DispatcherPresenter.h"
#include <list>
#include <set>
#include <string>
#include <iostream>
#include <iomanip> // Для setw
#include "../../header/repos/TokenRepository.h" // Include TokenRepository header

using namespace std;

void DispatcherPresenter::getDispatchers()
{
    try {
        *_output << "Dispatchers: " << endl;

        DispatcherRepository dispatcherRepo;
        string token = TokenRepository().getToken(); // Получаем токен
        list<DispatcherModel> dispatchers = dispatcherRepo.getDispatchers(token); // Получаем диспетчеров из репозитория
        if (dispatchers.empty()) {
            *_output << "No dispatchers found." << endl;
            return;
        }
        // Выводим список диспетчеров
        *_output << setw(10) << "ID"
                 << setw(10) << "FirstName"
                 << setw(10) << "LastName"
                 << setw(10) << "Email"
                 << setw(10) << "Password"
                 << setw(10) << "IsBanned" << endl;
        for (auto dispatcher : dispatchers) {
            *_output << setw(10) << dispatcher.getId()
                     << setw(10) << dispatcher.getFirstname()
                     << setw(10) << dispatcher.getLastname()
                     << setw(10) << dispatcher.getEmail()
                     << setw(10) << dispatcher.getPassword()
                     << setw(10) << (dispatcher.getIsBanned() ? "Yes" : "No") << endl;
        }
    } catch (const int& status) {
        *_output << "Error getting dispatchers. Status: " << status << endl;
        if (status == 500) {
            *_output << "Internal server error. Please try again later." << endl;
        } else if (status == 400) {
            *_output << "Bad request. Please check your input." << endl;
        } else if (status == 403) {
            *_output << "Forbidden access. You do not have permission." << endl;
        } else if (status == 401) {
            *_output << "Unauthorized access" << endl;
        }
    } catch (...) {
        *_output << "Unknown error. Call to support" << endl;
    }
}

void DispatcherPresenter::updateDispatcher() {
    try {
        long int dispatcherId;
        try {
            string id1;
            *_output << "Enter dispatcher ID to update: ";
            *_input >> id1;
            dispatcherId = stol(id1);
        } catch (...){
            throw 400;
        }
        string newFirstName, newLastName, newEmail, newPassword;
        bool newIsBanned = false; // Инициализируем переменную
        bool isBannedProvided = false; // Флаг, указывающий, было ли введено значение

        *_output << "Enter new first name (leave - to keep current): ";
        *_input >> newFirstName;

        *_output << "Enter new last name (leave - to keep current): ";
        *_input >> newLastName;

        *_output << "Enter new email (leave - to keep current): ";
        *_input >> newEmail;

        *_output << "Enter new password (leave - to keep current): ";
        *_input >> newPassword;

        *_output << "Is banned (1 for Yes, 0 for No, leave - to keep current): ";
        string isBannedInput;
        *_input >> isBannedInput; // Читаем ввод в строку

        if (!isBannedInput.empty()) {
            newIsBanned = (isBannedInput == "1"); // Устанавливаем значение в зависимости от ввода
            isBannedProvided = true; // Устанавливаем флаг
        }
        DispatcherModel updatedDispatcher(dispatcherId,
                                          newFirstName.empty() ? "" : newFirstName,
                                          newLastName.empty() ? "" : newLastName,
                                          newEmail.empty() ? "" : newEmail,
                                          newPassword.empty() ? "" : newPassword,
                                          isBannedProvided ? newIsBanned : false, // Используем флаг для определения, обновлять ли значение
                                          set<RoleModel>()); // Здесь можно обновить роли

        DispatcherRepository dispatcherRepo;
        string token = TokenRepository().getToken(); // Получаем токен
        set<string> updateFields;

        // Определяем, какие поля нужно обновить
        if (newFirstName != "-") updateFields.insert("firstName");
        if (newLastName != "-") updateFields.insert("lastName");
        if (newEmail != "-") updateFields.insert("email");
        if (newPassword != "-") updateFields.insert("password");
        if (isBannedProvided) updateFields.insert("isBanned");

        // Отправляем обновленного диспетчера на сервер
        DispatcherModel result = dispatcherRepo.updateDispatchers(updatedDispatcher, updateFields, token);

        // Проверяем, был ли обновлён диспетчер, например, по ID или другим критериям
        *_output << "Dispatcher updated successfully!" << endl;
        *_output << left;
        *_output << setw(10) << "ID"
                 << setw(10) << "FirstName"
                 << setw(10) << "LastName"
                 << setw(10) << "Email"
                 << setw(10) << "Password"
                 << setw(10) << "IsBanned" << endl;

        *_output << setw(10) << result.getId()
                 << setw(10) << result.getFirstname()
                 << setw(10) << result.getLastname()
                 << setw(10) << result.getEmail()
                 << setw(10) << result.getPassword()
                 << setw(10) << (result.getIsBanned() ? "Yes" : "No") << endl;
    } catch (const int& status) {
        *_output << "Error updating dispatcher. Status: " << status << endl;
        if (status == 500) {
            *_output << "Internal server error. Please try again later." << endl;
        } else if (status == 400) {
            *_output << "Bad request. Please check your input." << endl;
        } else if (status == 403) {
            *_output << "Forbidden access. You do not have permission." << endl;
        } else if (status == 401) {
            *_output << "Unauthorized access" << endl;
        }
    } catch (...) {
        *_output << "Unknown error. Call to support" << endl;
    }
}

void DispatcherPresenter::getDispatcherById() {
    try {
        long int id;
        try {
            string id1;
            *_output << "Enter dispatcher ID" << endl;
            *_input >> id1;
            id = stol(id1);
        } catch (...) {
            *_output << "Entered wrong data" << endl;
        }
        DispatcherRepository dispatcherRepo;
        string token = TokenRepository().getToken(); // Получаем токен
        DispatcherModel dispatcher = dispatcherRepo.getDispatcherById(id, token);
        *_output << "ID: " << dispatcher.getId()
                 << ", First Name: " << dispatcher.getFirstname()
                 << ", Last Name: " << dispatcher.getLastname()
                 << ", Email: " << dispatcher.getEmail()
                 << ", Is Banned: " << (dispatcher.getIsBanned() ? "Yes" : "No")
                 << endl;
    } catch (const int& status) {
        *_output << "Error getting dispatcher. Status: " << status << endl;
        if (status == 500) {
            *_output << "Internal server error. Please try again later." << endl;
        } else if (status == 400) {
            *_output << "Bad request. Please check your input." << endl;
        } else if (status == 403) {
            *_output << "Forbidden access. You do not have permission." << endl;
        } else if (status == 401) {
            *_output << "Unauthorized access" << endl;
        }
    } catch (...) {
        *_output << "Unknown error. Call to support" << endl;
    }
}