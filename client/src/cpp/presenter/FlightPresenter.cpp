#include "../../header/presentation/FlightPresenter.h"
#include <list>
#include <string>
#include <iostream>
#include "../../header/repos/TokenRepository.h" // Include TokenRepository header

using namespace std;

void FlightPresenter::getAllFlights()
{
    *_output << "Flights: " << std::endl;

    FlightRepository flightRepo;
    string token = TokenRepository().getToken(); // Получаем токен
    list<FlightModel> flights = flightRepo.getAllFlights(token); // Получаем рейсы из репозитория

    // Выводим список рейсов
    for (auto& flight : flights) {
        *_output << "ID: " << flight.getId()
                 << ", Start Time: " << flight.getTimestampStart()
                 << ", End Time: " << flight.getTimestampEnd()
                 << ", Dispatcher ID: " << flight.getDispatcherId()
                 << ", Plane ID: " << flight.getPlaneId()
                 << ", Airport ID: " << flight.getAirportId()
                 << std::endl;
    }
}

void FlightPresenter::createFlight() {
    try {
        long int dispatcherId, planeId, airportId;
        long int timestampStart, timestampEnd;

        *_output << "Enter dispatcher ID: ";
        *_input >> dispatcherId;

        *_output << "Enter plane ID: ";
        *_input >> planeId;

        *_output << "Enter airport ID: ";
        *_input >> airportId;

        FlightModel newFlight(0, 0, 0, dispatcherId, planeId, airportId); // Создаем новый объект рейса
        FlightRepository flightRepo;
        string token = TokenRepository().getToken(); // Получаем токен

        // Отправляем новый рейс на сервер и получаем результат
        FlightModel result = flightRepo.createFlight(newFlight, token);

        // Проверяем, был ли рейс успешно создан, например, по ID или другим критериям
        if (result.getId() != 0) { // Предполагаем, что 0 - это значение, которое указывает на неудачу
            *_output << "Flight created successfully!" << std::endl;
            *_output << "Flight ID: " << result.getId() << std::endl; // Выводим ID созданного рейса
        } else {
            *_output << "Error creating flight!" << std::endl;
        }
    } catch (int& e) {
        // Обработка ошибок
        if (e == 500) {
            *_output << "vse slomalos' peredelivay" << std::endl;
        }
        if (e == 400) {
            *_output << "Wrong request. Pizdui otsuda" << std::endl;
        }
        if (e == 403) {
            *_output << "Forbidden move. Try when u ll become more cool" << std::endl;
        }
        if (e == 409) {
            *_output << "Vam naznachili strelku - CONFLICT!" << std::endl;
        }
        if (e == 401) {
            *_output << "User  is unauthorized. Oluh" << std::endl;
        } else {
            *_output << "Call to support, +79092840120, its pizdec" << std::endl;
        }
    }
}