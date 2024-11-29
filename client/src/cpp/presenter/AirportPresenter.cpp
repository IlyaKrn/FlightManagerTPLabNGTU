#include "../../header/presentation/AirportPresenter.h"
#include <list>
#include <set>
#include "../../header/models/AirportModel.h"
#include "../../header/repos/AirportRepository.h"
#include <iomanip> // Для std::setw

void AirportPresenter::updateAirport()
{
    try {
        long int airportId;
        *_output << "Enter airport ID to update: ";
        *_input >> airportId;

        std::string newName;
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
        std::string token; // токен
        std::set<std::string> updateFields;

        if (!newName.empty()) updateFields.insert("name");
        if (newSize > 0) updateFields.insert("size");
        if (newX >= 0) updateFields.insert("x");
        if (newY >= 0) updateFields.insert("y");

        AirportModel result = airportRepo.updateAirport(updatedAirport, updateFields, token);

        *_output << "Airport updated successfully!" << std::endl;
        *_output << std::left; // Выравнивание по левому краю
        *_output << std::setw(10) << "ID"
            << std::setw(30) << "Name"
            << std::setw(10) << "Size"
            << std::setw(20) << "Coordinates" << std::endl;
        *_output << "Error updating airport!" << std::endl;
    } catch (int& e) {
        if (e == 500) {
            *_output << "vse slomalos' peredelivay" << std::endl;
        }
        if (e == 400)
            *_output << "Wrong request. Pizdui otsuda" << std::endl;
        if (e == 403)
            *_output << "Forbidden move. Try when u ll become more cool" << std::endl;
        if (e == 409)
            *_output << "Vam naznachili strelku - CONFLICT!" << std::endl;
        if (e == 401)
            *_output << "User  is unauthorized. Oluh" << std::endl;
        else
            *_output << "Call to support, +79092840120, its pizdec" << std::endl;
    }
}

void AirportPresenter::deleteAirport()
{
    try {
        long int airportId;
        *_output << "Enter airport ID to delete: ";
        *_input >> airportId;

        AirportRepository airportRepo;
        std::string token; // токен

        bool result = airportRepo.deleteAirport(airportId, token);

        if (result) {
            *_output << "Airport deleted successfully, good boy!" << std::endl;
        } else {
            *_output << "Error deleting airport, dolbaeb!" << std::endl;
        }
    } catch (int& e) {
        if (e == 500) {
            *_output << "vse slomalos' peredelivay" << std::endl;
        }
        if (e == 400)
            *_output << "Wrong request. Pizdui otsuda" << std::endl;
        if (e == 403)
            *_output << "Forbidden move. Try when u ll become more cool" << std::endl;
        if (e == 409)
            *_output << "Vam naznachili strelku - CONFLICT!" << std::endl;
        if (e == 401)
            *_output << "User  is unauthorized. Oluh" << std::endl;
        else
            *_output << "Call to support, +79092840120, its pizdec" << std::endl;
    }
}