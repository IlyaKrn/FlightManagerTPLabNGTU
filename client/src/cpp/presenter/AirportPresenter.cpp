#include "../../header/presentation/AirportPresenter.h"

#include <list>

#include "../../header/models/AirportModel.h"

using namespace std;

void AirportPresenter::getAirports()
{
    *_output << "Airports: " << std::endl;
    list<AirportModel> airports; //get airports from server
    //write table of airports
}

void AirportPresenter::createAirport()
{
    string airportName;
    *_input >> airportName;
    //get fields and create new airport? send it to server and print result (successful/error message)
}

void AirportPresenter::updateAirport()
{

}

void AirportPresenter::deleteAirport()
{

}

void PlanePresenter::getPlain()
{

}