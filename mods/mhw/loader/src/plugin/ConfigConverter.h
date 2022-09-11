#pragma once

#include <yaml-cpp/yaml.h>

#include <map>
#include <string>

#include "../loader/log.h"
#include "config.h"

namespace YAML {
  using loader::Config;
  using loader::LogLevel;
  std::map<std::string, LogLevel> logLevels = { { "DEBUG", LogLevel::DEBUG },
                                                { "INFO", LogLevel::INFO },
                                                { "WARNING", LogLevel::WARN },
                                                { "ERROR", LogLevel::ERR } };

  template <>
  struct convert<Config> {
    static bool decode(const Node& node, Config& rhs) {
      rhs.enablePluginLoader = node["enablePluginLoader"].as<bool>(false);
      rhs.logcmd = node["logcmd"].as<bool>(false);
      rhs.logfile = node["logfile"].as<bool>(false);
      rhs.logLevel = logLevels.at(node["logLevel"].as<std::string>("ERROR"));
      rhs.outputEveryPath = node["outputEveryPath"].as<bool>(false);
      return true;
    }
  };
}  // namespace YAML
