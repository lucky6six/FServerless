#include <stdio.h>
#include <stdlib.h>
#include "httplib.h"

void doGetHi(const httplib::Request& req, httplib::Response& res)
{
    res.set_content("666", "text/plain");
}

int main(int argc, char *argv[])
{
    httplib::Server server;
    server.Get("/hi", doGetHi);
    server.listen("0.0.0.0", 8081);
    return 0;
}