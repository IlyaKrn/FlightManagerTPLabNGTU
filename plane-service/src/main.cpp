#include <cpp-httplib/httplib.h>
#include "header/controllers/AirportController.h"
#include "header/Config.h"

using namespace std;


int main(int argc, char** argv[])
{
    httplib::Server server;
    AirportController().configure(&server);
    server.listen(SERVER_HOST, SERVER_PORT);
}

