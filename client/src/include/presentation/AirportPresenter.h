#pragma once

#include "IPresenter.h"

namespace src
{
    class AirportPresenter : public src::IPresenter {

    public:
        AirportPresenter(std::ostream *output, std::istream *input): IPresenter(output, input) {}

        void getAirports();
        void createAirport();
        void updateAirport();
        void deleteAirport();

    };
}