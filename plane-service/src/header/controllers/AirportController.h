#pragma once
#include "IController.h"
#include "../services/AirportService.h"

class AirportController : public IController {
public:
    void configure(httplib::Server* server) override;

};
