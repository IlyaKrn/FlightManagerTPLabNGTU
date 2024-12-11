#include "../../header/presentation/TimePresenter.h"
#include <iostream>
#include "../../header/repos/TokenRepository.h" // Include TokenRepository header

using namespace std;

    void TimePresenter::getCurrentTime() {
        TimeRepository timeRepo;
        string token = TokenRepository().getToken(); // Получаем токен авторизации

        try {
            string currentTime = timeRepo.getCurrentTime(token);
            *_output << "Current Time: " << currentTime << endl;
        } catch (const int& status) {
            *_output << "Error fetching current time. Status: " << status << endl;
            if (status == 500) {
                *_output << "Internal server error. Please try again later." << endl;
            } else if (status == 400) {
                *_output << "Bad request. Please check your input." << endl;
            } else if (status == 403) {
                *_output << "Forbidden access. You do not have permission." << endl;
            } else if (status == 401) {
                *_output << "Unauthorized access. Please log in." << endl;
            }
        }
    }

void TimePresenter::addTime() {
    long int timeToAdd;
    *_output << "Enter time to add (in seconds): ";
    *_input >> timeToAdd;

    TimeRepository timeRepo;
    string token = TokenRepository().getToken(); // Получаем токен авторизации

    try {
        bool result = timeRepo.addTime(timeToAdd, token);
        if (result) {
            *_output << "Time added successfully!" << endl;
        } else {
            *_output << "Error adding time!" << endl;
        }
    } catch (const int& status) {
        *_output << "Error adding time. Status: " << status << endl;
        if (status == 500) {
            *_output << "Internal server error. Please try again later." << endl;
        } else if (status == 400) {
            *_output << "Bad request. Please check your input." << endl;
        } else if (status == 403) {
            *_output << "Forbidden access. You do not have permission." << endl;
        } else if (status == 401) {
            *_output << "Unauthorized access. Please log in." << endl;
        }
    }
}