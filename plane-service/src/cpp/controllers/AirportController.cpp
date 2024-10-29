#include "../../header/controllers/AirportController.h"
#include "../../header/Config.h"

#include <json/single_include/nlohmann/json.hpp>

#include "../../header/repos/AirportRepository.h"

using namespace nlohmann;
using namespace httplib;
using namespace std;

void AirportController::configure(Server* server)
{
    // sample request handlers
    server->Get(SAMPLE_MAPPING, [this](const Request&, Response& response)
    {
        try
        {

            cout << AirportRepository().getAirports(1, "dff").size() << endl;
            //TODO("replace to here service method invocation and writing result to list")
            json result;
            result["name"] = "some name";
            result["id"] = "some id";

            response.set_content(result.dump(), "application/json");
        }
        catch (...)
        {
            cout << "AirportController::AirportController: exception occured" << endl;
            response.status = 500;
        }
    });

    server->Post(SAMPLE_MAPPING, [&](const Request& request, Response& response)
    {
        try
        {
            //TODO("replace to here service method invocation and writing result to list")
            json result = json::parse(request.body);

            response.set_content(result.dump(), "application/json");
        }
        catch (...)
        {
            cout << "AirportController::AirportController: exception occured" << endl;
            response.status = 500;
        }
    });

    //TODO("write here other api handlers with airports")
}
