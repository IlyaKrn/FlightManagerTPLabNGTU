#pragma once

#include "IPresenter.h"

namespace src
{
    class FlightPresenter : public IPresenter {
    public:
        FlightPresenter(std::ostream *output, std::istream *input): IPresenter(output, input) {}

        void getAllFlights();
        void createFlight();
    };
}