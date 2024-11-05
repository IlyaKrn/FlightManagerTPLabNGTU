#pragma once
#include "IController.h"
#include "../services/PlaneService.h"

class PlaneController : public IController {
private:
    PlaneService serv;
public:
    void configure(httplib::Server* server) override;

};