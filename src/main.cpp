#include <iostream>
#include <string_view>
#include <exception>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib/httplib.h>

#include "util.h"


int main() {
    Json::Value conf = LoadJson("./config.json");
    httplib::SSLServer svr(conf["ssl_cert_path"].asCString(), conf["ssl_key_path"].asCString());

    svr.set_mount_point("/static", conf["static_path"].asCString());

    svr.Get("/hey", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("<html><body><h1>Hey smsg!</h1></body></html>", "text/html");
    });

    svr.listen(conf["server_ip"].asString(), conf["server_port"].asInt());
}
