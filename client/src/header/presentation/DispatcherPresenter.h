#pragma once

#include "IPresenter.h"
#include "../../header/models/DispatcherModel.h"
#include "../../header/repos/DispatcherRepository.h"

class DispatcherPresenter : public IPresenter {
public:
    DispatcherPresenter(std::ostream *output, std::istream *input): IPresenter(output, input) {}

    void getDispatchers();
    void updateDispatcher();
};