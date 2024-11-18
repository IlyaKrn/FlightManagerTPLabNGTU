#include "../../header/controllers/TimeController.h"

#include "../../Config.h"
using namespace std;
using namespace httplib;
void TimeController::configure(Server* server)
{
    server->Get(TIME_GET_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            long int time = serv.getCurrentTime();
            res.status = 200;
            res.set_content(to_string(time), "text/plain");
        } catch (int& e)
        {
            cout << "exception occured " << e << endl;
            res.status = e;
        } catch (const exception& e)
        {
            cout << "exception occured" << e.what() << endl;
            res.status = 500;
        }
    });
    server->Post(TIME_SKIP_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            long int skip = 0;
            skip = stol(req.get_param_value("skip"));
            serv.skipTime(skip);
            res.status = 200;
            res.set_content("skipped " + to_string(skip) + " seconds", "text/plain");
        } catch (int& e)
        {
            cout << "exception occured " << e << endl;
            res.status = e;
        } catch (const exception& e)
        {
            cout << "exception occured" << e.what() << endl;
            res.status = 500;
        }
    });
}

