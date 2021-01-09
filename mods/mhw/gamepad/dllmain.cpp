// dllmain.cpp : Defines the entry point for the DLL application.
// #include <functional>

#include "loader.h"
#pragma comment (lib, "loader.lib")

#include "stuff.h"
#pragma comment (lib, "stuff.lib")

#include "gamepad/GamepadDispatcher.h"

using loader::LOG;
using loader::DEBUG;
using stuff::json::parseHexString;

using namespace stuff::functions;
using namespace gamepad;

static GamepadDispatcher instance;

IGamepadDispatcher& gamepad::GetDispatcher() {
    return instance;
}

PointerBiConsumer original = nullptr;

void PollCtrlHook(long long p1, long long p2) {
    original(p1, p2);
    instance.update(*(Gamepad*)p1);
    return;
}

void hookem() {
    auto PollCtrl = parseHexString(stuff::json::loadAddresses()["PollController()"]);
    MH_Initialize();
    // PointerBiConsumer PollCtrl = nullptr;
    // auto hook = std::bind_front(PollCtrlHook, PollCtrl);
    QueueHook(PollCtrl, &PollCtrlHook, &original);
    MH_ApplyQueued();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        hookem();
        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
