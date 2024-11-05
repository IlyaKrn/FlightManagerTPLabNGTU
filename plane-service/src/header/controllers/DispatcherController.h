#pragma once
#include "IController.h"
#include "../services/DispatcherService.h"
class DispatcherController : public IController
{
private:
    DispatcherService serv;
public:
    void configure(httplib::Server* server) override;
};