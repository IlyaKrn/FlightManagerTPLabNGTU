#include "../../header/presentation/TimePresenter.h"

using namespace std;

void TimePresenter::getCurrentTime() {
    string token; // Здесь должен быть токен авторизации
    TimeRepository timeRepo;

    try {
        long int currentTime = timeRepo.getCurrentTime(token);
        *_output << "Current Time: " << currentTime << endl;
    } catch (const int& status) {
        *_output << "Error fetching current time. Status: " << status << endl;
    }
}

void TimePresenter::addTime() {
    long int timeToAdd;
    *_output << "Enter time to add (in seconds): ";
    *_input >> timeToAdd;

    string token; // Здесь должен быть токен авторизации
    TimeRepository timeRepo;

    try {
        bool result = timeRepo.addTime(timeToAdd, token);
        if (result) {
            *_output << "Time added successfully!" << endl;
        } else {
            *_output << "Error adding time!" << endl;
        }
    } catch (const int& status) {
        *_output << "Error adding time. Status: " << status << endl;
    }
}