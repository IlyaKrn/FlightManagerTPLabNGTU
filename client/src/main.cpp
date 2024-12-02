#include "header/presentation/AirportPresenter.h"
#include "header/presentation/DispatcherPresenter.h"
#include "header/presentation/FlightPresenter.h"
#include "header/presentation/IdentityPresenter.h"
#include "header/presentation/IPresenter.h"
#include "header/presentation/PlanePresenter.h"
#include "header/presentation/TimePresenter.h"


using namespace std;


int main(int argc, char* argv[])
{
  while(1){
    cout << "Select action:" << endl;
    cout << "1. action1" << endl;
    cout << "2. action2" << endl;
    cout << "3. action3" << endl;
    string command;
    cin >> command;
    switch(command){
        case '1':
            AirportPresenter().getAll();
          break;
        case '2':

          break;
        case '3':

          break;
        case '4':

          break;
        default:

          break;
  }
}

