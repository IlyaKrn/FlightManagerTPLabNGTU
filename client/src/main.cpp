#include "header/presentation/AirportPresenter.h"
#include "header/presentation/DispatcherPresenter.h"
#include "header/presentation/FlightPresenter.h"
#include "header/presentation/IdentityPresenter.h"
#include "header/presentation/IPresenter.h"
#include "header/presentation/PlanePresenter.h"
#include "header/presentation/TimePresenter.h"

using namespace std;

int main(int argc, char* argv[])
{
    while (true) {
        cout << "Select action:" << endl;
        cout << "1. Manage Airports" << endl;
        cout << "2. Manage Dispatchers" << endl;
        cout << "3. Manage Flights" << endl;
        cout << "4. Manage Planes" << endl;
        cout << "5. Manage Time" << endl;
        cout << "6. Exit" << endl;

        string command;
        cin >> command;

        if (command == "1") {
            AirportPresenter airportPresenter(&cout, &cin);
            cout << "Select action for Airports:" << endl;
            cout << "1. Create Airport" << endl;
            cout << "2. Update Airport" << endl;
            cout << "3. Delete Airport" << endl;
            string airportAction;
            cin >> airportAction;

            if (airportAction == "1") {
                airportPresenter.createAirport();
            } else if (airportAction == "2") {
                airportPresenter.updateAirport();
            } else if (airportAction == "3") {
                airportPresenter.deleteAirport();
            } else {
                cout << "Invalid action for Airports!" << endl;
            }
        } else if (command == "2") {
            DispatcherPresenter dispatcherPresenter(&cout, &cin);
            cout << "Select action for Dispatchers:" << endl;
            cout << "1. Get Dispatchers" << endl;
            cout << "2. Update Dispatcher" << endl;
            string dispatcherAction;
            cin >> dispatcherAction;

            if (dispatcherAction == "1") {
                dispatcherPresenter.getDispatchers();
            } else if (dispatcherAction == "2") {
                dispatcherPresenter.updateDispatcher();
            } else {
                cout << "Invalid action for Dispatchers!" << endl;
            }
        } else if (command == "3") {
            FlightPresenter flightPresenter(&cout, &cin);
            cout << "Select action for Flights:" << endl;
            cout << "1. Get All Flights" << endl;
            cout << "2. Create Flight" << endl;
            string flightAction;
            cin >> flightAction;

            if (flightAction == "1") {
                flightPresenter.getAllFlights();
            } else if (flightAction == "2") {
                flightPresenter.createFlight();
            } else {
                cout << "Invalid action for Flights!" << endl;
            }
        } else if (command == "4") {
            PlanePresenter planePresenter(&cout, &cin);
            cout << "Select action for Planes:" << endl;
            cout << "1. Get Planes" << endl;
            cout << "2. Create Plane" << endl;
            cout << "3. Update Plane" << endl;
            cout << "4. Delete Plane" << endl;
            string planeAction;
            cin >> planeAction;

            if (planeAction == "1") {
                planePresenter.getPlanes();
            } else if (planeAction == "2") {
                planePresenter.createPlane();
            } else if (planeAction == "3") {
                planePresenter.updatePlane();
            } else if (planeAction == "4") {
                planePresenter.deletePlane();
            } else {
                cout << "Invalid action for Planes!" << endl;
            }
        } else if (command == "5") {
            TimePresenter timePresenter(&cout, &cin);
            cout << "Select action for Time:" << endl;
            cout << "1. Get Current Time" << endl;
            cout << "2. Add Time" << endl;
            string timeAction;
            cin >> timeAction;

            if (timeAction == "1") {
                timePresenter.getCurrentTime();
            } else if (timeAction == "2") {
                timePresenter.addTime();
            } else {
                cout << "Invalid action for Time!" << endl;
            }
        } else if (command == "6") {
            cout << "Exiting..." << endl;
            break; // Выход из цикла и завершение программы
        } else {
            cout << "Invalid command!" << endl;
        }
    }

    return 0;
}

