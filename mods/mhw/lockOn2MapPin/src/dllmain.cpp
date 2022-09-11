// dllmain.cpp : Defines the entry point for the DLL application.
#include <hook/hook.h>

#include "plugin/LockOn2MapPin.h"

using plugin::LockOn2MapPin;

LockOn2MapPin CaptainHook;

using HookTarget = void (*)(int64_t, uint64_t);
HookTarget original = nullptr;
// previousSomething = -255 if was not locked on previously, 0 otherwise
void LockOnIncrement(int64_t ptr, uint64_t previousSomething) {
  original(ptr, previousSomething);
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
