#include "../../header/presentation/FlightPresenter.h"
#include <list>
#include <string>
#include <iostream>
#include "../../header/repos/TokenRepository.h" // Include TokenRepository header
#include <iomanip>
using namespace std;

void FlightPresenter::getAllFlights()
{
    try {
        *_output << "Flights: " << endl;

        FlightRepository flightRepo;
        string token = TokenRepository().getToken(); // Получаем токен
        list<FlightModel> flights = flightRepo.getAllFlights(token); // Получаем рейсы из репозитория
        if (flights.empty()) {
            *_output << "No flights found." << endl;
            return;
        }
        // Выводим список рейсов
        *_output << setw(10) << "ID"
                 << setw(10) << "dispatcherId"
                 << setw(10) << "planeId"
                 << setw(10) << "airportId" << endl;

        for (auto flight : flights){
            *_output << setw(10) << flight.getId()
                     << setw(10) << flight.getDispatcherId()
                     << setw(10) << flight.getPlaneId()
                     << setw(10) << flight.getAirportId() << endl;
        }
    } catch (const int& status) {
        *_output << "Error getting flights. Status: " << status << endl;
        if (status == 500) {
            *_output << "Internal server error. Please try again later." << endl;
        } else if (status == 400) {
            *_output << "Bad request. Please check your input." << endl;
        } else if (status == 403) {
            *_output << "Forbidden access. You do not have permission." << endl;
        } else if (status == 401) {
            *_output << "Unauthorized access. Please log in." << endl;
        }
    } catch (...) {
        *_output << "Unknown error. Call to support" << endl;
    }
}

void FlightPresenter::createFlight() {
    try {
        long int dispatcherId, planeId, airportId;
        try {
            string dispatcherId1, planeId1, airportId1;
            *_output << "Enter dispatcher ID: ";
            *_input >> dispatcherId1;
            dispatcherId = stol(dispatcherId1);

            *_output << "Enter plane ID: ";
            *_input >> planeId1;
            planeId = stol(planeId1);

            *_output << "Enter airport ID: ";
            *_input >> airportId1;
            airportId = stol(airportId1);
        } catch (...) {
            throw 400;
        }
        FlightModel newFlight(0, 0, 0, dispatcherId, planeId, airportId); // Создаем новый объект рейса
        FlightRepository flightRepo;
        string token = TokenRepository().getToken();
        // Отправляем новый рейс на сервер и получаем результат
        FlightModel result = flightRepo.createFlight(newFlight, token);

        // Проверяем, был ли рейс успешно создан, например, по ID или другим критериям
        *_output << "Flight created successfully!" << std::endl;
        *_output << setw(10) << "ID"
                 << setw(10) << "dispatcherId"
                 << setw(10) << "planeId"
                 << setw(10) << "airportId" << endl;

        *_output << setw(10) << result.getId()
            << setw(10) << result.getDispatcherId()
            << setw(10) << result.getPlaneId()
            << setw(10) << result.getAirportId() << endl;
    } catch (const int& status) {
        *_output << "Error getting plane. Status: " << status << endl;
        if (status == 500) {
            *_output << "Internal server error. Please try again later." << endl;
        } else if (status == 400) {
            *_output << "Bad request. Please check your input." << endl;
        } else if (status == 403) {
            *_output << "Forbidden access. You do not have permission." << endl;
        } else if (status == 409) {
            *_output << "Conflict. This plane can be in flight or params of airport are unsuitable" << endl;
        } else if (status == 401) {
            *_output << "Unauthorized access. Please log in." << endl;
        }
    } catch (...) {
        *_output << "Unknown error. Call to support" << endl;
    }
}