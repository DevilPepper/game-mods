#pragma once

#include "../loader/log.h"

namespace loader {
  class Config {
   public:
    bool logfile;
    bool logcmd;
    LogLevel logLevel;
    bool outputEveryPath;
    bool enablePluginLoader;
  };

  Config loadConfig();
}  // namespace loader
