// dllmain.cpp : Defines the entry point for the DLL application.
#include <hook/hook.h>

#include "plugin/LockOn2MapPin.h"

using namespace stuff;

LockOn2MapPin CaptainHook;

using HookTarget = void (*)(uintptr_t);
HookTarget original = nullptr;
void LockOnIncrement(uintptr_t ptr) {
  original(ptr);
  CaptainHook.updatePin();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
      hook::init();
      hook::queue(CaptainHook.addresses.fnLockOnIncrement, &LockOnIncrement, &original);
      hook::apply();

      break;
    }
    case DLL_PROCESS_DETACH: {
      hook::unhook();
      break;
    }
    default:
      break;
  }
  return TRUE;
}
