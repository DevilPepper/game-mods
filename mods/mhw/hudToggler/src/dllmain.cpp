// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <hook/hook.h>

#include <chrono>
#include <thread>

#include "plugin/HUDHookHelper.h"

using namespace stuff;
using plugin::HUDHookHelper;

HUDHookHelper CaptainHook;
std::jthread hudChecker;

void toggleHUD(std::stop_token token) {
  while (!token.stop_requested()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    CaptainHook.writeHUD();
  }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
      std::jthread actualHUDChecker(toggleHUD);
      actualHUDChecker.swap(hudChecker);
      break;
    }
    case DLL_PROCESS_DETACH: {
      hudChecker.request_stop();
      hudChecker.join();
      break;
    }
    default:
      break;
  }
  return TRUE;
}
