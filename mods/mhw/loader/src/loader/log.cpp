#include "log.h"

#include <ctime>
#include <fstream>
#include <iostream>
#include <map>

namespace loader {

  LogLevel MinLogLevel = INFO;
  bool logcmd = false;
  bool logfile = false;

  void setLogParams(LogLevel MinLogLevel, bool logcmd, bool logfile) {
    loader::MinLogLevel = MinLogLevel;
    loader::logcmd = logcmd;
    loader::logfile = logfile;
  }

  // Copypasta from somewhere
  void BindStdHandlesToConsole() {
    // TODO: Add Error checking.

    // Redirect the CRT standard input, output, and error handles to the console
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stderr);
    freopen("CONOUT$", "w", stdout);

    // Note that there is no CONERR$ file
    HANDLE hStdout = CreateFile("CONOUT$",
                                GENERIC_READ | GENERIC_WRITE,
                                FILE_SHARE_READ | FILE_SHARE_WRITE,
                                nullptr,
                                OPEN_EXISTING,
                                FILE_ATTRIBUTE_NORMAL,
                                nullptr);
    HANDLE hStdin = CreateFile("CONIN$",
                               GENERIC_READ | GENERIC_WRITE,
                               FILE_SHARE_READ | FILE_SHARE_WRITE,
                               nullptr,
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL,
                               nullptr);

    SetStdHandle(STD_OUTPUT_HANDLE, hStdout);
    SetStdHandle(STD_ERROR_HANDLE, hStdout);
    SetStdHandle(STD_INPUT_HANDLE, hStdin);

    // Clear the error state for each of the C++ standard stream objects.
    std::wclog.clear();
    std::clog.clear();
    std::wcout.clear();
    std::cout.clear();
    std::wcerr.clear();
    std::cerr.clear();
    std::wcin.clear();
    std::cin.clear();
  }

  // TODO: Maybe keep the file open for the session?
  void logToFile(const char* stamp, const char* msg) {
    if (logfile) {
      std::ofstream o("loader.log", std::ios::app);
      o << "[ " << stamp << " ] " << msg;
      o.flush();
    }
  }

  void logToConsole(int l, const char* stamp, const char* msg) {
    // TODO: static inside a function?
    static HANDLE console = nullptr;
    if (logcmd) {
      if (!console) {
        AllocConsole();
        BindStdHandlesToConsole();
        SetConsoleTitle("Stracker's Loader");
        console = GetStdHandle(STD_OUTPUT_HANDLE);
      }
      SetConsoleTextAttribute(console, FOREGROUND_GREEN);
      WriteConsole(console, "[ ", 2, nullptr, nullptr);
      WriteConsole(console, stamp, static_cast<DWORD>(strlen(stamp)), nullptr, nullptr);
      WriteConsole(console, " ] ", 3, nullptr, nullptr);

      if (l == INFO || l == DEBUG) {
        SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
      }
      if (l == WARN) {
        SetConsoleTextAttribute(
            console,
            FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
      }
      if (l == ERR) {
        SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
      }
      WriteConsole(console, msg, static_cast<DWORD>(strlen(msg)), nullptr, nullptr);
      SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    }
  }

  void _log(LogLevel l, const char* s) {
    if (l < MinLogLevel) {
      return;
    }

    time_t mytime = time(nullptr);
    tm mytm;
    localtime_s(&mytm, &mytime);
    char stamp[128] = { 0 };
    strftime(stamp, sizeof(stamp), "%H:%M:%S", &mytm);

    logToFile(stamp, s);
    logToConsole(l, stamp, s);
  }

  LOG::LOG(LogLevel level) : logLevel(level) {}

  LOG::~LOG() {
    stream << std::endl;
    stream.flush();
    _log(logLevel, stream.str().c_str());
  }
}  // namespace loader
