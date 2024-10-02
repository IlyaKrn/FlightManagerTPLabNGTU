#include "../../header/controllers/AirportController.h"

void AirportController::configure(httplib::Server* server)
{
    server->Get("/api/airport/get", [this](const httplib::Request &, httplib::Response &res) {
        //TODO("replace to here service method invocation and writing result to list")
        std::string json = "{sample json}";
        //TODO("convert list to json (use additional lib or manually")

        res.set_content(json, "application/json");
    });
}
