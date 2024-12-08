#pragma once
#include "IController.h"
#include "../services/AirportService.h"
#include "../utils/Logger.h"
class AirportController : public IController {
    AirportService serv;
    Logger log;
public:
    void configure(httplib::Server* server) override;

};
