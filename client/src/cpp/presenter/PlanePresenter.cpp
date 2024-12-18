#include "../../header/presentation/PlanePresenter.h"
#include <iostream>
#include "../../header/repos/TokenRepository.h" // Include TokenRepository header
#include <iomanip>
using namespace std;

void PlanePresenter::getPlanes() {
    PlaneRepository planeRepo;
    string token = TokenRepository().getToken(); // Получаем токен авторизации

    try {
        list<PlaneModelResponse> planes = planeRepo.getPlanes(token);
        if (planes.empty()) {
            *_output << "No planes found." << endl;
            return;
        }
        *_output << "Planes: " << std::endl;
        *_output << setw(10) << "ID"
                 << setw(10) << "Name"
                 << setw(10) << "Pilot"
                 << setw(20) << "Built Year"
                 << setw(20) << "Broken Percentage"
                 << setw(10) << "Speed"
                 << setw(25) << "Min Airport Size"
                 << setw(10) << "Coordinates" << endl;

        for (auto& plane : planes) {
            *_output << setw(10) << plane.getId()
                     << setw(10) << plane.getName()
                     << setw(10) << plane.getPilot()
                     << setw(20) << plane.getBuiltYear()
                     << setw(20) << plane.getBrokenPercentage()
                     << setw(10) << plane.getSpeed()
                     << setw(25) << plane.getMinAirportSize()
                     << setw(10) << "(" << plane.getX() << "," << plane.getY() << ")" << endl;
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
    } catch (...) {
        *_output << "Unknown error. Call to support" << endl;
    }
}

void PlanePresenter::createPlane() {
    try {
        string name, pilot;
        int builtYear, speed, minAirportSize;
        try {
            *_output << "Enter plane name: ";
            *_input >> name;

            *_output << "Enter pilot name: ";
            *_input >> pilot;

            string builtYear1, speed1, minAirportSize1;
            *_output << "Enter built year: ";
            *_input >> builtYear1;
            builtYear = stoi(builtYear1);

            *_output << "Enter speed: ";
            *_input >> speed1;
            speed = stoi(speed1);

            *_output << "Enter minimum airport size: ";
            *_input >> minAirportSize1;
            minAirportSize = stoi(minAirportSize1);
        } catch (...) {
            throw 400;
        }
        PlaneModel newPlane(0, name, pilot, builtYear, 0, speed, minAirportSize);
        PlaneRepository planeRepo;
        string token = TokenRepository().getToken(); // Получаем токен авторизации

        // Отправляем новый объект самолета на сервер и получаем результат
        PlaneModel result = planeRepo.createPlane(newPlane, token);

        // Проверяем, был ли самолет успешно создан, например, по ID или другим критериям
        *_output << "Plane created successfully!" << std::endl;
        *_output << setw(10) << "ID"
                 << setw(10) << "Name"
                 << setw(10) << "Pilot"
                 << setw(20) << "Built Year"
                 << setw(20) << "Broken Percentage"
                 << setw(10) << "Speed"
                 << setw(20) << "Min Airport Size" << endl;


        *_output << setw(10) << result.getId()
                 << setw(10) << result.getName()
                 << setw(10) << result.getPilot()
                 << setw(20) << result.getBuiltYear()
                 << setw(20) << result.getBrokenPercentage()
                 << setw(10) << result.getSpeed()
                 << setw(20) << result.getMinAirportSize() << endl;
    } catch (const int& status) {
        *_output << "Error creating plane. Status: " << status << std::endl;
        if (status == 500) {
            *_output << "Internal server error. Please try again later." << std::endl;
        } else if (status == 400) {
            *_output << "Bad request. Please check your input." << std::endl;
        } else if (status == 403) {
            *_output << "Forbidden access. You do not have permission." << std::endl;
        } else if (status == 409) {
            *_output << "Conflict. Plane size is to big for start airport" << std::endl;
        } else if (status == 401) {
            *_output << "Unauthorized access" << std::endl;
        }
    } catch (...) {
        *_output << "Unknown error. Call to support" << endl;
    }
}

void PlanePresenter::updatePlane() {
    try {
        long int id;
        string name, pilot;
        int builtYear, speed, minAirportSize;
        set<string> updates;
        try {
            string id1, name1, pilot1;
            *_output << "Enter plane ID to update: ";
            *_input >> id1;
            id = stol(id1);

            *_output << "Enter new plane name (leave - to keep current): ";
            *_input >> name1;
            if (name1 != "-"){
                name = name1;
                updates.insert("name");
            }
            else
                name = "";
            *_output << "Enter new pilot name (leave - to keep current): ";
            *_input >> pilot1;
            if (pilot1 != "-"){
                pilot = pilot1;
                updates.insert("pilot");
            }
            else
                pilot = "";

            *_output << "Enter new built year (leave - to keep current): ";
            string builtYearInput;
            *_input >> builtYearInput;
            if (builtYearInput != "-") {
                builtYear = stoi(builtYearInput);
                updates.insert("builtYear");
            } else
                builtYear = -1;

            *_output << "Enter new speed (leave - to keep current): ";
            string speedInput;
            *_input >> speedInput;
            if (speedInput != "-") {
                speed = stoi(speedInput);
                updates.insert("speed");
            } else
                speed = -1;

            *_output << "Enter new minimum airport size (leave blank to keep current): ";
            string minAirportSizeInput;
            *_input >> minAirportSizeInput;
            if (minAirportSizeInput != "-") {
                minAirportSize = stoi(minAirportSizeInput);
                updates.insert("minAirportSize");
            } else
                minAirportSize = -1;
        } catch (...) {
            throw 400;
        }
        PlaneModel updatedPlane(id, name, pilot, builtYear,0, speed, minAirportSize);
        PlaneRepository planeRepo;
        string token = TokenRepository().getToken();
        PlaneModel result = planeRepo.updatePlane(updatedPlane, updates, token);

        *_output << "Plane updated successfully!" << std::endl;
        *_output << setw(10) << "ID"
                 << setw(10) << "Name"
                 << setw(10) << "Pilot"
                 << setw(20) << "Built Year"
                 << setw(20) << "Broken Percentage"
                 << setw(10) << "Speed"
                 << setw(20) << "Min Airport Size" << endl;


        *_output << setw(10) << result.getId()
                 << setw(10) << result.getName()
                 << setw(10) << result.getPilot()
                 << setw(20) << result.getBuiltYear()
                 << setw(20) << result.getBrokenPercentage()
                 << setw(10) << result.getSpeed()
                 << setw(20) << result.getMinAirportSize() << endl;

    } catch (const int& status) {
        *_output << "Error updating plane. Status: " << status << std::endl;
        if (status == 500) {
            *_output << "Internal server error. Please try again later." << std::endl;
        } else if (status == 400) {
            *_output << "Bad request. Please check your input." << std::endl;
        } else if (status == 403) {
            *_output << "Forbidden access. You do not have permission." << std::endl;
        } else if (status == 401) {
            *_output << "Unauthorized access" << std::endl;
        }
    } catch (...) {
        *_output << "Unknown error. Call to support" << endl;
    }
}

void PlanePresenter::deletePlane() {
    long int id;
    try {
        string id1;
        *_output << "Enter plane ID to delete: ";
        *_input >> id1;
        id = stol(id1);
    } catch(...){
        throw 400;
    }

    PlaneRepository planeRepo;
    string token = TokenRepository().getToken(); // Получаем токен авторизации

    try {
        bool result = planeRepo.deletePlane(id, token);
        if (result) {
            *_output << "Plane deleted successfully!" << std::endl;
        } else {
            *_output << "Error deleting plane!" << endl;
        }
    } catch (const int& status) {
        *_output << "Error deleting plane. Status: " << status << endl;
        if (status == 500) {
            *_output << "Internal server error. Please try again later." << endl;
        } else if (status == 400) {
            *_output << "Bad request. Please check your input." << endl;
        } else if (status == 403) {
            *_output << "Forbidden access. You do not have permission." << endl;
        } else if (status == 404) {
            *_output << "Plane not found. Please check the ID." << endl;
        } else if (status == 401) {
            *_output << "Unauthorized access" << endl;
        }
    } catch (...) {
        *_output << "Unknown error. Call to support" << endl;
    }
}