// dllmain.cpp : Defines the entry point for the DLL application.

#include <filesystem>
#include <string>
#include <thread>
#include <tuple>
#include <vector>

#include "loader/log.h"
#include "plugin/config.h"
#include "plugin/dll.h"
#include "windows.h"

std::vector<std::jthread> threads;

const char* loader::GameVersion = "???";
static std::string GameVersionString;

void FindVersion() {
  auto* window = GetForegroundWindow();
  auto titleLength = GetWindowTextLength(window) + 1;
  TCHAR title[35];
  GetWindowText(window, title, titleLength);
  std::string_view titleView((char*)title);

  auto begin = titleView.find('(') + 1;
  auto size = titleView.find(')') - begin;
  GameVersionString = std::string{ titleView.substr(begin, size) };
  loader::GameVersion = GameVersionString.c_str();
}

extern "C" {
__declspec(dllexport) extern void Initialize(void* memModule) {
  try {
    auto config = loader::loadConfig();
    if (config.enablePluginLoader && std::filesystem::exists("nativePC\\plugins")) {
      FindVersion();
      loader::setLogParams(config.logLevel, config.logcmd, config.logfile);

      dll::LoadAllPluginDlls(memModule);
      dll::initSystemMessages();
      threads.emplace_back(dll::watch);
    }
    return;
  } catch (std::exception e) {
    MessageBox(nullptr, "STRACKER'S LOADER ERROR", e.what(), MB_OK);
  }
}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  return TRUE;
}
