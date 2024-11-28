#pragma once

#include "IPresenter.h"
#include "../../header/models/DispatcherModel.h"
#include "../../header/repos/DispatcherRepository.h"

class DispatcherPresenter : public IPresenter {
public:
    void getDispatchers();
    void createDispatcher();
    void updateDispatcher();
    void deleteDispatcher();
};