#pragma once
#include "IController.h"

class AirportController : public IController {
public:
    void configure(httplib::Server* server) override;

};
