// dllmain.cpp : Defines the entry point for the DLL application.
// #include <functional>

#include <MHW/strings.h>
#include <Windows.h>
#include <gamepad.h>
#include <hook/hook.h>
#include <types/address.h>
#include <yaml-cpp/yaml.h>

using namespace stuff;
using gamepad::Gamepad;
using MHW::addressFile;
using stuff::types::Pointer;

using HookedConsumer = void (*)(int64_t, int64_t, int64_t, int64_t);
HookedConsumer original = nullptr;
void PollCtrlHook(int64_t p1, int64_t p2, int64_t p3, int64_t p4) {
  original(p1, p2, p3, p4);
  gamepad::GetDispatcher().update(*(Gamepad*)p1);
  return;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
      auto exeBase = (Pointer)GetModuleHandle(NULL);
      auto yaml = YAML::LoadFile(MHW::getFilePath(addressFile));
      auto PollCtrl = yaml["functions"]["fnPollController"].as<Pointer>();

      hook::init();
      hook::queue(exeBase + PollCtrl, &PollCtrlHook, &original);
      hook::apply();
      break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
      hook::unhook();
      break;
  }
  return TRUE;
}
