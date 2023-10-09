#include <iostream>
#include <string_view>
#include <exception>
#include <filesystem>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib/httplib.h>

#include "util.h"


int main() {
    Json::Value conf = LoadJson("./app/config.json");

    httplib::SSLServer svr(conf["ssl_cert_path"].asCString(), conf["ssl_key_path"].asCString());

    const std::filesystem::path static_path(conf["static_path"].asCString());
    svr.set_mount_point("/static", static_path.c_str());

    svr.Get("/hey", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("<html><body><h1>Hey smsg!</h1></body></html>", "text/html");
    });

    svr.Get("/", [&static_path](const httplib::Request &, httplib::Response &res) {
        res.set_content(LoadTextFile(static_path / "html/messenger.html"), "text/html");
    });

    svr.listen(conf["server_ip"].asString(), conf["server_port"].asInt());
}
