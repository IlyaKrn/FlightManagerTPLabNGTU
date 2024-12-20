#pragma once

#include "IPresenter.h"

namespace src
{
    class TimePresenter : public IPresenter {
    public:
        TimePresenter(std::ostream *output, std::istream *input): IPresenter(output, input) {}

        void getCurrentTime();
        void addTime();
    };
}