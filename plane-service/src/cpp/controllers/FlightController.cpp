#include "../../header/controllers/FlightController.h"
#include "../../header/Config.h"
#include <json/single_include/nlohmann/json.hpp>



using namespace nlohmann;
using namespace httplib;
using namespace std;

void FlightController::configure(Server* server)
{
    // sample request handlers
    server->Get(FLIGHT_GET_MAPPING, [this](const Request&, Response& response)
    {
        try
        {


            json result;
            response.set_content(result.dump(), "application/json");
        }
        catch (...)
        {
            cout << "FlightController::FlightController: exception occured" << endl;
            response.status = 500;
        }
    });
    server->Post(FLIGHT_CREATE_MAPPING, [&](const Request& request, Response& response)
    {
        try
        {

        }
        catch (...)
        {
            cout << "FlightController::FlightController: exception occured" << endl;
            response.status = 500;
        }
    });
    server->Get(FLIGHT_GET_MAPPING, [&](const Request& request, Response& response)
    {
        try
        {

        }
        catch (...)
        {
            cout << "FlightController::FlightController: exception occured" << endl;
            response.status = 500;
        }
    });
}