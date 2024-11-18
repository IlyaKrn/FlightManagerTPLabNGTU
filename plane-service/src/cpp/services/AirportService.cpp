#include "../../header/services/AirportService.h"

using namespace std;
list<AirportModel> AirportService::getAllAirports(string token)
{
    try
    {
        set<string> permissions;
        permissions.insert("getAllAirports");
        bool isAllowed = ident.authorize(permissions, token);
        if (!isAllowed)
        {
            throw string("401");
        }
        list<AirportModel> airports = repo.getAirports();
        return airports;
    } catch (const string& e)
    {
        throw string(e);
    }
}

AirportModel AirportService::getAirportById(long int id, string token)
{
    try
    {
        set<string> permissions;
        permissions.insert("getAirportById");
        bool isAllowed = ident.authorize(permissions ,token);
        if (!isAllowed)
        {
            throw string("401");
        }
        list<AirportModel> airports = repo.getAirports(&id);
        return airports.front();

    } catch (const string& e)
    {
        throw string(e);
    }
}

bool AirportService::createAirport(AirportModel airport, string token)
{
    try
    {
        set<string> permissions;
        permissions.insert("createAirport");
        bool isAllowed = ident.authorize(permissions ,token);
        if (!isAllowed)
        {
            throw string("401");
        }
        bool res = repo.createAirport(airport);
        return res;
    } catch (const string& e)
    {
        throw string(e);
    }
}
bool AirportService::updateAirport(AirportModel airport, set<string> update, string token)
{
    try
    {
        set<string> permissions;
        permissions.insert("updateAirport");
        bool isAllowed = ident.authorize(permissions ,token);
        if (!isAllowed)
        {
            throw string("401");
        }
        AirportModel n_airport = getAirportById(airport.getId(), token);
        if (update.count("name") > 0)
        {
            n_airport.setName(airport.getName());
        }
        if (update.count("size") > 0)
        {
            n_airport.setSize(airport.getSize());
        }
        if (update.count("x") > 0)
        {
            n_airport.setX(airport.getX());
        }
        if (update.count("y") > 0)
        {
            n_airport.setY(airport.getY());
        }
        bool res = repo.updateAirport(n_airport, update);
        return res;
    } catch (const string& e)
    {
        throw string(e);
    }
}
bool AirportService::deleteAirport(long int id, string token)
{
    try
    {
        set<string> permissions;
        permissions.insert("deleteAirport");
        bool isAllowed = ident.authorize(permissions ,token);
        if (!isAllowed)
        {
            throw string("401");
        }
        bool res = repo.deleteAirport(id);
        return res;
    } catch (const string& e)
    {
        throw string(e);
    }
}