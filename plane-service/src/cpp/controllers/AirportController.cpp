#include "../../header/controllers/AirportController.h"
#include "../../Config.h"

#include <json/single_include/nlohmann/json.hpp>

#include "../../header/repos/AirportRepository.h"

using namespace nlohmann;
using namespace httplib;
using namespace std;

void AirportController::configure(Server* server)
{
    server->Get(SAMPLE_MAPPING, [this](const Request&, Response& response)
    {
        try
        {
            response.status = 200;
        }
        catch (...)
        {
            response.status = 500;
        }
    });
}
