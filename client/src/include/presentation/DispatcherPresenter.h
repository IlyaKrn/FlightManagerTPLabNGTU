#pragma once

#include "IPresenter.h"

namespace src
{
    class DispatcherPresenter : public IPresenter {
    public:
        DispatcherPresenter(std::ostream *output, std::istream *input): IPresenter(output, input) {}

        void getDispatchers();
        void updateDispatcher();
        void getDispatcherById();
    };
}