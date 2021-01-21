// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>

#include "gamepad.h"
#pragma comment(lib, "GamepadLib.lib")

#include "plugin/Hermes.h"

using gamepad::Gamepad;
using gamepad::GamepadToken;

Hermes hermes;
GamepadToken token;

void callback(const Gamepad& gamepad) {
  hermes.handleInput(gamepad);
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
