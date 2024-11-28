#include "../../header/presentation/DispatcherPresenter.h"
#include <list>
#include <set>
#include <string>
#include <iostream>

using namespace std;

void DispatcherPresenter::getDispatchers()
{
    *_output << "Dispatchers: " << std::endl;

    DispatcherRepository dispatcherRepo;
    string token; // Здесь должен быть токен авторизации
    list<DispatcherModel> dispatchers = dispatcherRepo.getDispatchers(token); // Получаем диспетчеров из репозитория

    // Выводим список диспетчеров
    for (auto& dispatcher : dispatchers) {
        *_output << "ID: " << dispatcher.getId()
                 << ", First Name: " << dispatcher.getFirstname()
                 << ", Last Name: " << dispatcher.getLastname()
                 << ", Email: " << dispatcher.getEmail()
                 << ", Is Banned: " << (dispatcher.getIsBanned() ? "Yes" : "No")
                 << std::endl;
    }
}

void DispatcherPresenter::createDispatcher()
{
    string firstName, lastName, email, password;
    bool isBanned;

    *_output << "Enter first name: ";
    *_input >> firstName;

    *_output << "Enter last name: ";
    *_input >> lastName;

    *_output << "Enter email: ";
    *_input >> email;

    *_output << "Enter password: ";
    *_input >> password;

    *_output << "Is banned (1 for Yes, 0 for No): ";
    *_input >> isBanned;

    set<RoleModel> roles; // Здесь можно добавить роли, если нужно
    // Например, добавим роль DISPATCHER
    roles.insert(RoleModel::DISPATCHER);

    DispatcherModel newDispatcher(0, firstName, lastName, email, password, isBanned, roles); // Создаем новый объект диспетчера
    DispatcherRepository dispatcherRepo;
    string token; // Здесь должен быть токен авторизации

    // Отправляем нового диспетчера на сервер
    bool result = dispatcherRepo.createDispatcher(newDispatcher, token);

    if (result) {
        *_output << "Dispatcher created successfully!" << std::endl;
    } else {
        *_output << "Error creating dispatcher!" << std::endl;
    }
}

void DispatcherPresenter::updateDispatcher()
{
    long int dispatcherId;
    *_output << "Enter dispatcher ID to update: ";
    *_input >> dispatcherId;

    string newFirstName, newLastName, newEmail, newPassword;
    bool newIsBanned = false; // Инициализируем переменную
    bool isBannedProvided = false; // Флаг, указывающий, было ли введено значение

    *_output << "Enter new first name (leave blank to keep current): ";
    *_input >> newFirstName;

    *_output << "Enter new last name (leave blank to keep current): ";
    *_input >> newLastName;

    *_output << "Enter new email (leave blank to keep current): ";
    *_input >> newEmail;

    *_output << "Enter new password (leave blank to keep current): ";
    *_input >> newPassword;

    *_output << "Is banned (1 for Yes, 0 for No, leave blank to keep current): ";
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
    string token; // Здесь должен быть токен авторизации
    set<string> updateFields;

    // Определяем, какие поля нужно обновить
    if (!newFirstName.empty()) updateFields.insert("firstName");
    if (!newLastName.empty()) updateFields.insert("lastName");
    if (!newEmail.empty()) updateFields.insert("email");
    if (!newPassword.empty()) updateFields.insert("password");
    if (isBannedProvided) updateFields.insert("isBanned");

    // Отправляем обновленного диспетчера на сервер
    bool result = dispatcherRepo.updateDispatchers(updatedDispatcher, updateFields, token);

    if (result) {
        *_output << "Dispatcher updated successfully!" << std::endl;
    } else {
        *_output << "Error updating dispatcher!" << std::endl;
    }
}

void DispatcherPresenter::deleteDispatcher()
{
    long int dispatcherId;
    *_output << "Enter dispatcher ID to delete: ";
    *_input >> dispatcherId;

    DispatcherRepository dispatcherRepo;
    string token; // Здесь должен быть токен авторизации

    // Удаляем диспетчера с сервера
    bool result = dispatcherRepo.deleteDispatcher(dispatcherId, token);

    if (result) {
        *_output << "Dispatcher deleted successfully!" << std::endl;
    } else {
        *_output << "Error deleting dispatcher!" << std::endl;
    }
}