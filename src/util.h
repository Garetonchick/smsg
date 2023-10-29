#pragma once

#include <json/json.h>
#include <string>

Json::Value LoadJson(const std::string& file_path);
std::string LoadTextFile(const std::string& file_path);
