#include "../../header/presentation/PlanePresenter.h"
#include <iostream>

using namespace std;

void PlanePresenter::getPlanes() {
    string token; // Здесь должен быть токен авторизации
    PlaneRepository planeRepo;

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
    }
}

void PlanePresenter::createPlane() {
    long int id;
    string name, pilot;
    int builtYear, brokenPercentage, speed, minAirportSize;

    *_output << "Enter plane ID: ";
    *_input >> id;

    *_output << "Enter plane name: ";
    *_input >> name;

    *_output << "Enter pilot name: ";
    *_input >> pilot;

    *_output << "Enter built year: ";
    *_input >> builtYear;

    *_output << "Enter broken percentage: ";
    *_input >> brokenPercentage;

    *_output << "Enter speed: ";
    *_input >> speed;

    *_output << "Enter minimum airport size: ";
    *_input >> minAirportSize;

    PlaneModel newPlane(id, name, pilot, builtYear, brokenPercentage, speed, minAirportSize);
    PlaneRepository planeRepo;
    string token; // Здесь должен быть токен авторизации

    try {
        bool result = planeRepo.createPlane(newPlane, token);
        if (result) {
            *_output << "Plane created successfully!" << std::endl;
        } else {
            *_output << "Error creating plane!" << std::endl;
        }
    } catch (const int& status) {
        *_output << "Error creating plane. Status: " << status << std::endl;
    }
}

void PlanePresenter::updatePlane() {
    long int id;
    *_output << "Enter plane ID to update: ";
    *_input >> id;

    string name, pilot;
    int builtYear, brokenPercentage, speed, minAirportSize;
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

    *_output << "Enter new broken percentage (leave blank to keep current): ";
    string brokenPercentageInput;
    *_input >> brokenPercentageInput;
    if (!brokenPercentageInput.empty()) {
        brokenPercentage = stoi(brokenPercentageInput);
        updates.insert("brokenPercentage");
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
                            !name.empty() ? name : "",
                            !pilot.empty () ? pilot : "",
                            builtYear,
                            brokenPercentage,
                            speed,
                            minAirportSize);
    PlaneRepository planeRepo;
    string token; // Здесь должен быть токен авторизации

    try {
        bool result = planeRepo.updatePlane(updatedPlane, updates, token);
        if (result) {
            *_output << "Plane updated successfully!" << std::endl;
        } else {
            *_output << "Error updating plane!" << std::endl;
        }
    } catch (const int& status) {
        *_output << "Error updating plane. Status: " << status << std::endl;
    }
}

void PlanePresenter::deletePlane() {
    long int id;
    *_output << "Enter plane ID to delete: ";
    *_input >> id;

    PlaneRepository planeRepo;
    string token; // Здесь должен быть токен авторизации

    try {
        bool result = planeRepo.deletePlane(id, token);
        if (result) {
            *_output << "Plane deleted successfully!" << std::endl;
        } else {
            *_output << "Error deleting plane!" << std::endl;
        }
    } catch (const int& status) {
        *_output << "Error deleting plane. Status: " << status << std::endl;
    }
}