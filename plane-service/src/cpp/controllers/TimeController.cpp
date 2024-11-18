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
            long int skip = 0;
            try
            {
                skip = stol(req.get_param_value("skip"));
            } catch (...)
            {
                res.status = 400;
                return;
            }
            res.status = 200;
            res.set_content(to_string(skip), "text/plain");
        } catch (const exception& err)
        {
            cout << "TimeController::TimeController: exception occured" << err.what() << endl;
            res.status = 500;
        }
    });
    server->Post(TIME_SKIP_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            long int skip = 0;
            try
            {
                skip = stol(req.get_param_value("skip"));
            } catch (...)
            {
                res.status = 400;
                return;
            }
            serv.skipTime(skip);
            res.status = 200;
            res.set_content("skipped " + to_string(skip) + " seconds", "text/plain");
        } catch (const exception& err)
        {
            cout << "TimeController::TimeController: exception occured" << err.what() << endl;
            res.status = 500;
        }
    });
}

