#include <cpp-httplib/httplib.h>
#include "header/controllers/AirportController.h"

using namespace std;


int main(int argc, char** argv[])
{
    httplib::Server server;
    AirportController().configure(&server);
    server.listen("127.0.0.1", 8080);
}

