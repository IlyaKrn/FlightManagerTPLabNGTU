#pragma once

#include "IPresenter.h"

namespace src
{
    class PlanePresenter : public IPresenter {
    public:
        PlanePresenter(std::ostream *output, std::istream *input): IPresenter(output, input) {}

        void getPlanes();
        void createPlane();
        void updatePlane();
        void deletePlane();
    };
}