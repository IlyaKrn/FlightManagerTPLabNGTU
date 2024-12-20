#pragma once

#include "IPresenter.h"

namespace src
{
    class IdentityPresenter : public IPresenter {
    public:
        IdentityPresenter(std::ostream *output, std::istream *input): IPresenter(output, input) {}

        bool login();
        bool registerDispatcher();
    };
}