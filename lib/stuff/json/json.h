#pragma once

#include <nlohmann/json.hpp>

#include <vector>
#include <string>

using std::vector;
using std::string;

namespace stuff {
	namespace json {
        nlohmann::json loadConfig(string fileName);
        nlohmann::json loadAddresses();
        vector<intptr_t> parseHexStrings(nlohmann::json node);
        intptr_t parseHexString(nlohmann::json node);
    }
}
