#pragma once

#include "IPresenter.h"
#include "../../header/models/FlightModel.h"
#include "../../header/repos/FlightRepository.h"

class FlightPresenter : public IPresenter {
public:
    void getAllFlights();
    void createFlight();
    void updateFlight();
    void deleteFlight();
};