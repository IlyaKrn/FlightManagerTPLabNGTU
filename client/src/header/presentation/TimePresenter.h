#pragma once

#include "IPresenter.h"
#include "../../header/repos/TimeRepository.h"
#include <iostream>
#include <string>

class TimePresenter : public IPresenter {
public:
    void getCurrentTime();
    void addTime();
};