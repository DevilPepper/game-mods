// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>

#include "gamepad.h"
#pragma comment(lib, "GamepadLib.lib")

#include "counter/Counter.h"

using gamepad::Gamepad;

Counter counter;

void callback(const Gamepad& gamepad) {
  counter.handleInput(gamepad);
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
