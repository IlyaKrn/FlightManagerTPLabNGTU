#include "../../header/controllers/PlaneController.h"
#include "../../header/Config.h"
#include <json/single_include/nlohmann/json.hpp>



using namespace nlohmann;
using namespace httplib;
using namespace std;

void PlaneController::configure(Server* server)
{
    // sample request handlers
    server->Get(PLANE_GET_MAPPING, [this](const Request&, Response& response)
    {
        try
        {


            json result;
            response.set_content(result.dump(), "application/json");
        }
        catch (...)
        {
            cout << "PlaneController::PlaneController: exception occured" << endl;
            response.status = 500;
        }
    });

    server->Post(PLANE_CREATE_MAPPING, [&](const Request& request, Response& response)
    {
        try
        {

            json result = json::parse(request.body);

            response.set_content(result.dump(), "application/json");
        }
        catch (...)
        {
            cout << "PlaneController::PlaneController: exception occured" << endl;
            response.status = 500;
        }
    });

    server->Post(PLANE_UPDATE_MAPPING, [&](const Request& request, Response& response)
    {
        try
        {

        }
        catch (...)
        {
            cout << "PlaneController::PlaneController: exception occured" << endl;
            response.status = 500;
        }
    });
    server->Get(PLANE_GET_MAPPING, [&](const Request& request, Response& response)
    {
        try
        {

        }
        catch (...)
        {
            cout << "PlaneController::PlaneController: exception occured" << endl;
            response.status = 500;
        }
    });
    server->Delete(PLANE_DELETE_MAPPING, [&](const Request& request, Response& response)
    {
        try
        {

        }
        catch (...)
        {
            cout << "PlaneController::PlaneController: exception occured" << endl;
            response.status = 500;
        }
    });
}
