#include "../../header/controllers/DispatcherController.h"
#include "../../header/Config.h"
#include <json/single_include/nlohmann/json.hpp>



using namespace nlohmann;
using namespace httplib;
using namespace std;

void DispatcherController::configure(Server* server)
{
    // sample request handlers
    server->Get(DISPATCHER_GET_MAPPING, [this](const Request&, Response& response)
    {
        try
        {


            json result;
            response.set_content(result.dump(), "application/json");
        }
        catch (...)
        {
            cout << "DispatcherController::DispatcherController: exception occured" << endl;
            response.status = 500;
        }
    });
    server->Post(DISPATCHER_UPDATE_MAPPING, [&](const Request& request, Response& response)
    {
        try
        {

        }
        catch (...)
        {
            cout << "DispatcherController::DispatcherController: exception occured" << endl;
            response.status = 500;
        }
    });
    server->Get(DISPATCHER_GET_MAPPING, [&](const Request& request, Response& response)
    {
        try
        {

        }
        catch (...)
        {
            cout << "DispatcherController::DispatcherController: exception occured" << endl;
            response.status = 500;
        }
    });
}
