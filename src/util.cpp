#include "util.h"

#include <fstream>
#include <sstream>

Json::Value LoadJson(const std::string& file_path) {
    Json::Value val;
    std::ifstream ifs(file_path);

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

std::string LoadTextFile(const std::string& file_path) {
    std::ifstream is(file_path);
    std::stringstream ss;
    ss << is.rdbuf();
    return ss.str();
}
