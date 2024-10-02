#include <cpp-httplib/httplib.h>

using namespace std;


int main(int argc, char** argv[])
{
    httplib::Server server;
    server.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });
    server.listen("127.0.0.1", 8080);
}

