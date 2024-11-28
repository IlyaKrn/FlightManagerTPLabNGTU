#include "../../header/presentation/AirportPresenter.h"
#include <list>
#include <set>
#include "../../header/models/AirportModel.h"
#include "../../header/repos/AirportRepository.h"
#include <iomanip> // Для std::setw
using namespace std;

void AirportPresenter::getAirports()
{
    *_output << "Airports: " << std::endl;

    AirportRepository airportRepo;
    string token; // Здесь должен быть токен авторизации
    list<AirportModel> airports = airportRepo.getAllAirports(token); // Получаем аэропорты из репозитория

    // Выводим заголовки столбцов
    *_output << std::left; // Выравнивание по левому краю
    *_output << std::setw(10) << "ID"
             << std::setw(30) << "Name"
             << std::setw(10) << "Size"
             << std::setw(20) << "Coordinates" << std::endl;

    // Разделительная линия
    *_output << std::string(70, '-') << std::endl;

    // Выводим данные аэропортов
    for (auto& airport : airports) {
        *_output << std::setw(10) << airport.getId()
                 << std::setw(30) << airport.getName()
                 << std::setw(10) << airport.getSize()
                 << std::setw(20) << "(" << airport.getX() << ", " << airport.getY() << ")"
                 << std::endl;
    }
}

void AirportPresenter::createAirport()
{
    string airportName;
    int airportSize;
    double x, y;

    *_output << "Enter airport name: ";
    *_input >> airportName;

    *_output << "Enter airport size: ";
    *_input >> airportSize;

    *_output << "Enter airport coordinates (x y): ";
    *_input >> x >> y;

    AirportModel newAirport(0, airportName, airportSize, x, y);
    AirportRepository airportRepo;
    string token; // токен
    // Отправляем новый аэропорт на сервер
    bool result = airportRepo.createAirport(newAirport, token);

    if (result) {
        *_output << "Airport created successfully!" << std::endl;
    } else {
        *_output << "Error creating airport!" << std::endl;
    }
}

void AirportPresenter::updateAirport()
{
    long int airportId;
    *_output << "Enter airport ID to update: ";
    *_input >> airportId;

    string newName;
    int newSize;
    double newX, newY;

    *_output << "Enter new name (leave blank to keep current): ";
    *_input >> newName;

    *_output << "Enter new size (leave blank to keep current): ";
    *_input >> newSize;

    *_output << "Enter new coordinates (x y, leave empty to keep current): ";
    *_input >> newX >> newY;


    AirportModel updatedAirport(airportId, newName.empty() ? "" : newName, newSize > 0 ? newSize : -1, newX >= 0 ? newX : -1, newY >= 0 ? newY : -1);
    AirportRepository airportRepo;
    string token;
    set<string> updateFields;

    if (!newName.empty()) updateFields.insert("name");
    if (newSize > 0) updateFields.insert("size");
    if (newX >= 0) updateFields.insert("x");
    if (newY >= 0) updateFields.insert("y");


    bool result = airportRepo.updateAirport(updatedAirport, updateFields, token);

    if (result) {
        *_output << "Airport updated successfully!" << std::endl;
    } else {
        *_output << "Error updating airport!" << std::endl;
    }
}

void AirportPresenter::deleteAirport()
{
    long int airportId;
    *_output << "Enter airport ID to delete: ";
    *_input >> airportId;

    AirportRepository airportRepo;
    string token; //


    bool result = airportRepo.deleteAirport(airportId, token);

    if (result) {
        *_output << "Airport deleted successfully, good boy!" << std::endl;
    } else {
        *_output << "Error deleting airport, dolbaeb!" << std::endl;
    }
}