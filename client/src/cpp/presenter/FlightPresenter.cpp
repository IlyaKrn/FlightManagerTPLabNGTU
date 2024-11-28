#include "../../header/presentation/FlightPresenter.h"
#include <list>
#include <string>
#include <iostream>

using namespace std;

void FlightPresenter::getAllFlights()
{
    *_output << "Flights: " << std::endl;

    FlightRepository flightRepo;
    string token; // Здесь должен быть токен авторизации
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

void FlightPresenter::createFlight()
{
    long int dispatcherId, planeId, airportId;
    long int timestampStart, timestampEnd;

    *_output << "Enter dispatcher ID: ";
    *_input >> dispatcherId;

    *_output << "Enter plane ID: ";
    *_input >> planeId;

    *_output << "Enter airport ID: ";
    *_input >> airportId;

    *_output << "Enter start timestamp: ";
    *_input >> timestampStart;

    *_output << "Enter end timestamp: ";
    *_input >> timestampEnd;

    FlightModel newFlight(0, timestampStart, timestampEnd, dispatcherId, planeId, airportId); // Создаем новый объект рейса
    FlightRepository flightRepo;
    string token; // Здесь должен быть токен авторизации

    // Отправляем новый рейс на сервер
    bool result = flightRepo.createFlight(newFlight, token);

    if (result) {
        *_output << "Flight created successfully!" << std::endl;
    } else {
        *_output << "Error creating flight!" << std::endl;
    }
}

