#include "mhw-json.h"

#include "json/json.h"
#pragma comment(lib, "stuff.lib")

namespace MHW {
  nlohmann::json loadConfig(string fileName) {
    return stuff::json::loadConfig("nativePC/plugins/config/" + fileName);
  }
}  // namespace MHW
