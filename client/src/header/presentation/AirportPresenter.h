#pragma once
#include "IPresenter.h"

class AirportPresenter : public IPresenter {

public:
    void getAirports();
    void createAirport();
    void updateAirport();
    void deleteAirport();

};