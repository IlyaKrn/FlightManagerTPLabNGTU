#include "../../header/presentation/AirportPresenter.h"
#include <list>
#include <set>
#include "../../header/models/AirportModel.h"
#include "../../header/repos/AirportRepository.h"
#include <iomanip> // Для setw

using namespace std;
void AirportPresenter::getAirports() {
    try {
        AirportRepository airportRepo;
        string token; // Здесь должен быть токен авторизации

        // Получаем список аэропортов
        list<AirportModel> airports = airportRepo.getAllAirports(token);

        // Проверяем, есть ли аэропорты
        if (airports.empty()) {
            *_output << "No airports found." << endl;
            return;
        }

        // Выводим заголовки таблицы
        *_output << left; // Выравнивание по левому краю
        *_output << setw(10) << "ID"
                 << setw(30) << "Name"
                 << setw(10) << "Size"
                 << setw(20) << "Coordinates" << endl;

        // Выводим информацию о каждом аэропорте
        for (const auto& airport : airports) {
            *_output << setw(10) << airport.getId()
                     << setw(30) << airport.getName()
                     << setw(10) << airport.getSize()
                     << setw(20) << "(" << airport.getX() << ", " << airport.getY() << ")" << endl;
        }

    } catch (int& e) {
        // Обработка ошибок
        if (e == 500) {
            *_output << "vse slomalos' peredelivay" << endl;
        }
        if (e == 400)
            *_output << "Wrong request. Pizdui otsuda" << endl;
        if (e == 403)
            *_output << "Forbidden move. Try when u ll become more cool" << endl;
        if (e == 409)
            *_output << "Vam naznachili strelku - CONFLICT!" << endl;
        if (e == 401)
            *_output << "User  is unauthorized. Oluh" << endl;
        else
            *_output << "Call to support, +79092840120, its pizdec" << endl;
    }
}
void AirportPresenter::createAirport() {
    try {
        // Запрос данных у пользователя
        string name;
        int size;
        double x, y;

        *_output << "Enter airport name: ";
        *_input >> name;

        *_output << "Enter airport size: ";
        *_input >> size;

        *_output << "Enter airport coordinates (x y): ";
        *_input >> x >> y;

        // Создание модели аэропорта
        AirportModel newAirport(0, name, size, x, y); // ID будет 0, так как это новый аэропорт
        AirportRepository airportRepo;
        string token; // Здесь должен быть токен авторизации

        // Вызов метода для создания аэропорта
        AirportModel createdAirport = airportRepo.createAirport(newAirport, token);

        *_output << "Airport created successfully!" << endl;
        *_output << left; // Выравнивание по левому краю
        *_output << setw(10) << "ID"
                 << setw(30) << "Name"
                 << setw(10) << "Size"
                 << setw(20) << "Coordinates" << endl;

        *_output << setw(10) << createdAirport.getId()
                 << setw(30) << createdAirport.getName()
                 << setw(10) << createdAirport.getSize()
                 << setw(20) << "(" << createdAirport.getX() << ", " << createdAirport.getY() << ")" << endl;

    } catch (int& e) {
        // Обработка ошибок
        if (e == 500) {
            *_output << "vse slomalos' peredelivay" << endl;
        }
        if (e == 400)
            *_output << "Wrong request. Pizdui otsuda" << endl;
        if (e == 403)
            *_output << "Forbidden move. Try when u ll become more cool" << endl;
        if (e == 409)
            *_output << "Vam naznachili strelku - CONFLICT!" << endl;
        if (e == 401)
            *_output << "User  is unauthorized. Oluh" << endl;
        else
            *_output << "Call to support, +79092840120, its pizdec" << endl;
    }
}
void AirportPresenter::updateAirport()
{
    try {
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
        string token; // токен
        set<string> updateFields;

        if (!newName.empty()) updateFields.insert("name");
        if (newSize > 0) updateFields.insert("size");
        if (newX >= 0) updateFields.insert("x");
        if (newY >= 0) updateFields.insert("y");

        AirportModel result = airportRepo.updateAirport(updatedAirport, updateFields, token);

        *_output << "Airport updated successfully!" << endl;
        *_output << left; // Выравнивание по левому краю
        *_output << setw(10) << "ID"
            << setw(30) << "Name"
            << setw(10) << "Size"
            << setw(20) << "Coordinates" << endl;
        *_output << "Error updating airport!" << endl;
    } catch (int& e) {
        if (e == 500) {
            *_output << "vse slomalos' peredelivay" << endl;
        }
        if (e == 400)
            *_output << "Wrong request. Pizdui otsuda" << endl;
        if (e == 403)
            *_output << "Forbidden move. Try when u ll become more cool" << endl;
        if (e == 409)
            *_output << "Vam naznachili strelku - CONFLICT!" << endl;
        if (e == 401)
            *_output << "User  is unauthorized. Oluh" << endl;
        else
            *_output << "Call to support, +79092840120, its pizdec" << endl;
    }
}

void AirportPresenter::deleteAirport()
{
    try {
        long int airportId;
        *_output << "Enter airport ID to delete: ";
        *_input >> airportId;

        AirportRepository airportRepo;
        string token; // токен

        bool result = airportRepo.deleteAirport(airportId, token);

        if (result) {
            *_output << "Airport deleted successfully, good boy!" << endl;
        } else {
            *_output << "Error deleting airport, dolbaeb!" << endl;
        }
    } catch (int& e) {
        if (e == 500) {
            *_output << "vse slomalos' peredelivay" << endl;
        }
        if (e == 400)
            *_output << "Wrong request. Pizdui otsuda" << endl;
        if (e == 403)
            *_output << "Forbidden move. Try when u ll become more cool" << endl;
        if (e == 409)
            *_output << "Vam naznachili strelku - CONFLICT!" << endl;
        if (e == 401)
            *_output << "User  is unauthorized. Oluh" << endl;
        else
            *_output << "Call to support, +79092840120, its pizdec" << endl;
    }
}