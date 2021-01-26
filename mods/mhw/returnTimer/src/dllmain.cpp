// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>

#include "gamepad.h"
#pragma comment(lib, "GamepadLib.lib")

#include "plugin/ReturnTimer.h"

using gamepad::Gamepad;
using gamepad::GamepadToken;

ReturnTimer plugin;
GamepadToken token;

void callback(const Gamepad& gamepad) {
  plugin.handleInput(gamepad);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
      token = gamepad::GetDispatcher().registerCallback(&callback);
      break;
    case DLL_PROCESS_DETACH:
      gamepad::GetDispatcher().unregisterCallback(token);
      break;
    default:
      break;
  }
  return TRUE;
}
