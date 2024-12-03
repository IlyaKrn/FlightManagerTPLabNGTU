#pragma once

#include "IPresenter.h"
#include "../../header/models/PlaneModel.h"
#include "../../header/repos/PlaneRepository.h"
#include <list>
#include <set>
#include <string>

class PlanePresenter : public IPresenter {
public:
    PlanePresenter(std::ostream *output, std::istream *input): IPresenter(output, input) {}

    void getPlanes();
    void createPlane();
    void updatePlane();
    void deletePlane();
};