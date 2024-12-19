#include "../src/include/srclib.h"
#include <iostream>

using namespace std;
using namespace src;

int main(int argc, char* argv[])
{
    IdentityRepository().regist(DispatcherModel(0, "fn", "ln", "email", "pass", true, set<RoleModel>()));
    return 0;
}

