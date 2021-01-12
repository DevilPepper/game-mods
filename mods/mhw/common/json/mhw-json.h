#include <nlohmann/json.hpp>
#include <string>

using std::string;

namespace MHW {
  nlohmann::json loadConfig(string fileName);
}
