#pragma once
#include "IController.h"
#include "../services/AirportService.h"

class AirportController : public IController {
private:
    AirportService serv;
public:
    void configure(httplib::Server* server) override;

};
