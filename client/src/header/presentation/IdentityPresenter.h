#pragma once

#include "IPresenter.h"
#include "../../header/repos/IdentityRepository.h"
#include <set>
#include <string>

class IdentityPresenter : public IPresenter {
public:
    void login();
    void registerDispatcher();
};