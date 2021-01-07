#include "json.h"
#include <fstream>

namespace stuff {
    namespace json {
        nlohmann::json loadConfig(string fileName) {
            std::ifstream config("nativePC/plugins/config/" + fileName);
            return nlohmann::json::parse(config);
        }

        nlohmann::json loadAddresses() {
            return loadConfig("addresses.json");
        }

        vector<intptr_t> parseHexStrings(nlohmann::json node) {
            auto strings = node.get<vector<string>>();
            auto pointers = vector<intptr_t>();

            for ( string str : strings) {
                pointers.push_back(std::stoll(str, nullptr, 16));
            }
            return pointers;
        }
    }
}
