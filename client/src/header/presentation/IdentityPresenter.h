#pragma once

#include "IPresenter.h"
#include "../../header/repos/IdentityRepository.h"
#include <set>
#include <string>

class IdentityPresenter : public IPresenter {
public:
    IdentityPresenter(std::ostream *output, std::istream *input): IPresenter(output, input) {}

    bool login();
    bool registerDispatcher();
};