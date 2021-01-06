// dllmain.cpp : Defines the entry point for the DLL application.
#include <future>
#include <thread>
#include <chrono>

#include <windows.h>;

#include "loader.h"
#include "util.h"
#include "ghidra_export.h"
#pragma comment (lib, "loader.lib")

#include "stuff.h"
#include "Gamepad.h"
#pragma comment (lib, "stuff.lib")

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

using loader::LOG;
using loader::DEBUG;
using loader::ERR;
using std::string;
using std::vector;
using stuff::memory::readMem;
using stuff::memory::writeMem;

typedef void(__fastcall* PointerBiConsumer)(longlong, longlong);

HANDLE procHandle = NULL;
intptr_t mhw = 0x140000000;

vector<intptr_t> subtitle_setting{ 0x5073E80, 0x10A };
vector<intptr_t> subtitle_show{ 0x5224B90, 0x13e20, 0x332c };
vector<intptr_t> hud_settings{ 0x5073E80, 0xa8, 0x151F8C };

long long xor_settings = 0x0001000001000101;

bool SelectPressed = false;
bool L1Pressed = false;

void setHandle() {
    auto hGameWindow = FindWindow(NULL, "MONSTER HUNTER: WORLD(421409)");
    DWORD pid = NULL;
    GetWindowThreadProcessId(hGameWindow, &pid);

    procHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
}

void toggleSubtitles() {

    bool subs_setting;
    readMem(procHandle, mhw, subtitle_setting, &subs_setting, sizeof(bool));
    subs_setting ^= true;
    writeMem(procHandle, mhw, subtitle_setting, &subs_setting, sizeof(bool));

    bool subs_show;
    readMem(procHandle, mhw, subtitle_show, &subs_show, sizeof(bool));
    subs_show ^= true;
    writeMem(procHandle, mhw, subtitle_show, &subs_show, sizeof(bool));
}

void toggleHUD() {
    long long hud;
    readMem(procHandle, mhw, hud_settings, &hud, sizeof(long long));
    hud ^= xor_settings;
    writeMem(procHandle, mhw, hud_settings, &hud, sizeof(long long));

}

enum BTN_ACTION { PRESSED, RELEASED, LONG_PRESS, LONG_RELEASE };

BTN_ACTION btnPressed(Button btn, bool& pressed, uint32_t buttons) {
    auto button = Buttons[btn];
    if ((buttons & button) != 0) {
        if (!pressed) {
            pressed = true;
            return BTN_ACTION::PRESSED;
        }
        else {
            return BTN_ACTION::LONG_PRESS;
        }
    }
    else {
        if (pressed) {
            pressed = false;
            return BTN_ACTION::RELEASED;
        }
        else {
            return BTN_ACTION::LONG_RELEASE;
        }
    }
}

CreateHook((PointerBiConsumer)0x1418e8ea0, PollCtrlHook, void, longlong p1, longlong p2) {
    Gamepad* gamepad = (Gamepad*)p1;

    original(p1, p2);

    if(procHandle == NULL) {
        setHandle();
    }

    if (btnPressed(Button::Select, SelectPressed, gamepad->buttons) == PRESSED) {
        LOG(ERR) << std::hex << "Toggle Subtitles: " << Buttons[Button::Select];
        toggleSubtitles();
    }
    auto l1 = btnPressed(Button::L1, L1Pressed, gamepad->buttons);
    if (l1 == PRESSED) {
        LOG(ERR) << std::hex << "HUD On: " << Buttons[Button::L1];
        toggleHUD();
    } else if(l1 == RELEASED) {
        LOG(ERR) << "HUD Off";
        toggleHUD();
    }
   return;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        MH_Initialize();
        QueueHook(PollCtrlHook);
        MH_ApplyQueued();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
