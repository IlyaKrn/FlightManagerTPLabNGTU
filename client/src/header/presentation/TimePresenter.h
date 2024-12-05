#pragma once

#include "IPresenter.h"
#include "../../header/repos/TimeRepository.h"
#include <iostream>
#include <string>

class TimePresenter : public IPresenter {
public:
    TimePresenter(std::ostream *output, std::istream *input): IPresenter(output, input) {}

    void getCurrentTime();
    void addTime();
};