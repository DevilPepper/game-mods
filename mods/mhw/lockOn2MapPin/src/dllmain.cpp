// dllmain.cpp : Defines the entry point for the DLL application.
#include "MinHook.h "
#include "stuff.h"
#pragma comment(lib, "stuff.lib")

#include "hooky/LockOn2MapPin.h"

using namespace stuff::functions;

LockOn2MapPin CaptainHook;

// TODO: try currying LockOnIncrement()
PointerConsumer original = nullptr;
void LockOnIncrement(uintptr_t ptr) {
  original(ptr);
  CaptainHook.updatePin();
}

void hookem() {
  MH_Initialize();
  QueueHook(CaptainHook.addresses.get<intptr_t>("LockOnIncrement()"), &LockOnIncrement, &original);
  MH_ApplyQueued();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
      hookem();
      break;
    }
    default:
      break;
  }
  return TRUE;
}
