// dllmain.cpp : Defines the entry point for the DLL application.
// #include <functional>

#include <MinHook.h>

#include "gamepad.h"
#pragma comment(lib, "GamepadLib.lib")

#include "MHW-deps.h"
#include "MHW.h"
#pragma comment(lib, "mhw-common.lib")

using stuff::json::parseHexString;

using namespace stuff::functions;
using namespace gamepad;

PointerBiConsumer original = nullptr;

void PollCtrlHook(long long p1, long long p2) {
  original(p1, p2);
  gamepad::GetDispatcher().update(*(Gamepad*)p1);
  return;
}

void hookem() {
  auto PollCtrl = parseHexString(MHW::loadConfig("addresses.json")["PollController()"]);
  MH_Initialize();
  // PointerBiConsumer PollCtrl = nullptr;
  // auto hook = std::bind_front(PollCtrlHook, PollCtrl);
  QueueHook(PollCtrl, &PollCtrlHook, &original);
  MH_ApplyQueued();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
      hookem();
      break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
      break;
  }
  return TRUE;
}
