#include <iostream>
#include <string_view>
#include <fstream>
#include <exception>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib/httplib.h>
#include <jsoncpp/json/json.h>

Json::Value LoadJson(const char *file_name) {
    Json::Value val;
    std::ifstream ifs(file_name);

    if (!ifs.is_open()) {
        throw std::runtime_error("Failed to open json file");
    }

    Json::CharReaderBuilder builder;
    std::string errs;
    if (!Json::parseFromStream(builder, ifs, &val, &errs)) {
        throw std::runtime_error("Failed to load/parse json");
    }
    return val;
}

int main() {
    Json::Value conf = LoadJson("./config.json");
    httplib::SSLServer svr(conf["ssl_cert_path"].asCString(), conf["ssl_key_path"].asCString());

    svr.Get("/hey", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    svr.listen(conf["server_ip"].asString(), conf["server_port"].asInt());
}
