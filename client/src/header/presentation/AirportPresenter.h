#pragma once
#include "IPresenter.h"

class AirportPresenter : public IPresenter {

public:
    AirportPresenter(std::ostream *output, std::istream *input): IPresenter(output, input) {}

    void getAirports();
    void createAirport();
    void updateAirport();
    void deleteAirport();

};