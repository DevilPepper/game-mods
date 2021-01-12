// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>

#include "gamepad.h"
#pragma comment(lib, "GamepadHook.lib")

#include "hermes/Hermes.h"

using gamepad::Gamepad;

Hermes hermes;

void callback(const Gamepad& gamepad) {
  hermes.handleInput(gamepad);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
      gamepad::GetDispatcher().registerCallback(&callback);
      break;
    default:
      break;
  }
  return TRUE;
}
