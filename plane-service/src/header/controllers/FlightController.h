#pragma once
#include "IController.h"
#include "../services/FlightService.h"

class FlightController : public IController
{
private:
    FlightService serv;
public:
    void configure(httplib::Server* server) override;
};