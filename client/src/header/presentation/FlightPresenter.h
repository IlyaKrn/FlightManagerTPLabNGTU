#pragma once

#include "IPresenter.h"
#include "../../header/models/FlightModel.h"
#include "../../header/repos/FlightRepository.h"

class FlightPresenter : public IPresenter {
public:
    FlightPresenter(std::ostream *output, std::istream *input): IPresenter(output, input) {}

    void getAllFlights();
    void createFlight();
};