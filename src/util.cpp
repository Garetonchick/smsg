#include "util.h"
#include <fstream>
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