#include <iostream>
#include <thread>
// #define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib/httplib.h>

int main() {
    httplib::Server svr;

    svr.Get("/hey", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    svr.listen("0.0.0.0", 8080);
}
