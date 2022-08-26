// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <gamepad.h>
#include <hook/hook.h>

#include "plugin/HUDHookHelper.h"

using namespace stuff;
using gamepad::Gamepad;
using gamepad::GamepadToken;
using plugin::HUDHookHelper;

HUDHookHelper CaptainHook;
GamepadToken token;

void callback(const Gamepad& gamepad) {
  CaptainHook.handleInput(gamepad);
}

using InvokableConsumer = void (*)(int64_t, int64_t);
InvokableConsumer original = nullptr;
void toggleHUD(int64_t hudStruct, int64_t _unknown) {
  original(hudStruct, _unknown);
  CaptainHook.writeHUD((long long*)hudStruct);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
      token = gamepad::GetDispatcher().registerCallback(&callback);
      hook::init();
      hook::queue(0x141e42e30, &toggleHUD, &original);
      hook::apply();
      break;
    case DLL_PROCESS_DETACH:
      gamepad::GetDispatcher().unregisterCallback(token);
      hook::unhook();
      break;
    default:
      break;
  }
  return TRUE;
}
