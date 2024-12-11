#include "../../header/presentation/PlanePresenter.h"
#include <iostream>
#include "../../header/repos/TokenRepository.h" // Include TokenRepository header

using namespace std;

void PlanePresenter::getPlanes() {
    PlaneRepository planeRepo;
    string token = TokenRepository().getToken(); // Получаем токен авторизации

    try {
        list<PlaneModelResponse> planes = planeRepo.getPlanes(token);
        *_output << "Planes: " << std::endl;

        for (auto& plane : planes) {
            *_output << "ID: " << plane.getId()
                     << ", Name: " << plane.getName()
                     << ", Pilot: " << plane.getPilot()
                     << ", Built Year: " << plane.getBuiltYear()
                     << ", Broken Percentage: " << plane.getBrokenPercentage()
                     << ", Speed: " << plane.getSpeed()
                     << ", Min Airport Size: " << plane.getMinAirportSize()
                     << std::endl;
        }
    } catch (const int& status) {
        *_output << "Error fetching planes. Status: " << status << std::endl;
        if (status == 500) {
            *_output << "Internal server error. Please try again later." << std::endl;
        } else if (status == 400) {
            *_output << "Bad request. Please check your input." << std::endl;
        } else if (status == 403) {
            *_output << "Forbidden access. You do not have permission." << std::endl;
        } else if (status == 401) {
            *_output << "Unauthorized access. Please log in." << std::endl;
        }
    }
}

void PlanePresenter::createPlane() {
    string name, pilot;
    int builtYear, speed, minAirportSize;

    *_output << "Enter plane name: ";
    *_input >> name;

    *_output << "Enter pilot name: ";
    *_input >> pilot;

    *_output << "Enter built year: ";
    *_input >> builtYear;

    *_output << "Enter speed: ";
    *_input >> speed;

    *_output << "Enter minimum airport size: ";
    *_input >> minAirportSize;

    PlaneModel newPlane(0, name, pilot, builtYear, 0, speed, minAirportSize);
    PlaneRepository planeRepo;
    string token = TokenRepository().getToken(); // Получаем токен авторизации

    try {
        // Отправляем новый объект самолета на сервер и получаем результат
        PlaneModel result = planeRepo.createPlane(newPlane, token);

        // Проверяем, был ли самолет успешно создан, например, по ID или другим критериям
        if (result.getId() != 0) { // Предполагаем, что 0 - это значение, которое указывает на неудачу
            *_output << "Plane created successfully!" << std::endl;
            *_output << "Plane ID: " << result.getId() << std::endl; // Выводим ID созданного самолета
        } else {
            *_output << "Error creating plane!" << std::endl;
        }
    } catch (const int& status) {
        *_output << "Error creating plane. Status: " << status << std::endl;
        if (status == 500) {
            *_output << "Internal server error. Please try again later." << std::endl;
        } else if (status == 400) {
            *_output << "Bad request. Please check your input." << std::endl;
        } else if (status == 403) {
            *_output << "Forbidden access. You do not have permission." << std::endl;
        } else if (status == 409) {
            *_output << "Conflict! A plane with this ID might already exist." << std::endl;
        } else if (status == 401) {
            *_output << "Unauthorized access. Please log in." << std::endl;
        }
    }
}

void PlanePresenter::updatePlane() {
    long int id;
    *_output << "Enter plane ID to update: ";
    *_input >> id;

    string name, pilot;
    int builtYear = 0, speed = 0, minAirportSize = 0; // Initialize variables
    set<string> updates;

    *_output << "Enter new plane name (leave blank to keep current): ";
    *_input >> name;
    if (!name.empty()) updates.insert("name");

    *_output << "Enter new pilot name (leave blank to keep current): ";
    *_input >> pilot;
    if (!pilot.empty()) updates.insert("pilot");

    *_output << "Enter new built year (leave blank to keep current): ";
    string builtYearInput;
    *_input >> builtYearInput;
    if (!builtYearInput.empty()) {
        builtYear = stoi(builtYearInput);
        updates.insert("builtYear");
    }

    *_output << "Enter new speed (leave blank to keep current): ";
    string speedInput;
    *_input >> speedInput;
    if (!speedInput.empty()) {
        speed = stoi(speedInput);
        updates.insert("speed");
    }

    *_output << "Enter new minimum airport size (leave blank to keep current): ";
    string minAirportSizeInput;
    *_input >> minAirportSizeInput;
    if (!minAirportSizeInput.empty()) {
        minAirportSize = stoi(minAirportSizeInput);
        updates.insert("minAirportSize");
    }

    PlaneModel updatedPlane(id,
                            !name.empty() ? name : "", // If empty, keep current value
                            !pilot.empty() ? pilot : "",
                            builtYear,
                            0,
                            speed,
                            minAirportSize);
    PlaneRepository planeRepo;
    string token = TokenRepository().getToken(); // Получаем токен авторизации

    try {
        // Отправляем обновленный объект самолета на сервер и получаем результат
        PlaneModel result = planeRepo.updatePlane(updatedPlane, updates, token);

        // Проверяем, был ли самолет успешно обновлен, например, по ID или другим критериям
        if (result.getId() == id) { // Предполагаем, что ID совпадает с обновленным
            *_output << "Plane updated successfully!" << std::endl;
        } else {
            *_output << "Error updating plane!" << std::endl;
        }
    } catch (const int& status) {
        *_output << "Error updating plane. Status: " << status << std::endl;
        if (status == 500) {
            *_output << "Internal server error. Please try again later." << std::endl;
        } else if (status == 400) {
            *_output << "Bad request. Please check your input." << std::endl;
        } else if (status == 403) {
            *_output << "Forbidden access. You do not have permission." << std::endl;
        } else if (status == 404) {
            *_output << "Plane not found. Please check the ID." << std::endl;
        } else if (status == 401) {
            *_output << "Unauthorized access. Please log in." << std::endl;
        }
    }
}

void PlanePresenter::deletePlane() {
    long int id;
    *_output << "Enter plane ID to delete: ";
    *_input >> id;

    PlaneRepository planeRepo;
    string token = TokenRepository().getToken(); // Получаем токен авторизации

    try {
        bool result = planeRepo.deletePlane(id, token);
        if (result) {
            *_output << "Plane deleted successfully!" << std::endl;
        } else {
            *_output << "Error deleting plane!" << std::endl;
        }
    } catch (const int& status) {
        *_output << "Error deleting plane. Status: " << status << std::endl;
        if (status == 500) {
            *_output << "Internal server error. Please try again later." << std::endl;
        } else if (status == 400) {
            *_output << "Bad request. Please check your input." << std::endl;
        } else if (status == 403) {
            *_output << "Forbidden access. You do not have permission." << std::endl;
        } else if (status == 404) {
            *_output << "Plane not found. Please check the ID." << std::endl;
        } else if (status == 401) {
            *_output << "Unauthorized access. Please log in." << std::endl;
        }
    }
}