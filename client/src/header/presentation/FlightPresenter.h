#pragma once

#include "IPresenter.h"
#include "../../header/models/FlightModel.h"
#include "../../header/repos/FlightRepository.h"
#include "../../header/repos/TimeRepository.h"

class FlightPresenter : public IPresenter {
private:
    TimeRepository timer;
public:
    FlightPresenter(std::ostream *output, std::istream *input): IPresenter(output, input) {}

    void getAllFlights();
    void createFlight();
};