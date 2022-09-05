#pragma once

#include <sdkddkver.h>
#include <windows.h>

#include <sstream>
#include <vector>

#ifdef DINPUT8MHW_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

namespace loader {
  enum LogLevel { DEBUG = 0, INFO = 1, WARN = 2, ERR = 3 };

  void setLogParams(LogLevel MinLogLevel, bool logcmd, bool logfile);

  DllExport extern const char* GameVersion;
  DllExport extern LogLevel MinLogLevel;

  class DllExport LOG {
   private:
    std::stringstream stream;
    LogLevel logLevel;
    LOG(const LOG& o) = delete;
    LOG& operator=(const LOG& o) = delete;

   public:
    explicit LOG(LogLevel level);
    ~LOG();

    template <class T>
    LOG& operator<<(const T& x) {
      if (logLevel >= MinLogLevel)
        stream << x;
      return *this;
    }
  };
}  // namespace loader
