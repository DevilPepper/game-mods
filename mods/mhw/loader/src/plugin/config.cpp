#include "config.h"

#include <yaml-cpp/yaml.h>

#include "ConfigConverter.h"

namespace loader {
  Config loadConfig() {
    return YAML::LoadFile("loader-config.json").as<Config>();
  }
}  // namespace loader
