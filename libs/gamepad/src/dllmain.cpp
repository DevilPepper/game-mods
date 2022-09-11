// dllmain.cpp : Defines the entry point for the DLL application.
// #include <functional>
#include <Windows.h>

#include "gamepad/GamepadDispatcher.h"

static gamepad::GamepadDispatcher instance;

gamepad::IGamepadDispatcher& gamepad::GetDispatcher() {
  return instance;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  return TRUE;
}
