// dllmain.cpp : Defines the entry point for the DLL application.
#include <future>
#include <thread>
#include <chrono>

#include <windows.h>

#include "loader.h"
#include "util.h"
#pragma comment (lib, "loader.lib")

#include "stuff.h"
#pragma comment (lib, "stuff.lib")

using loader::LOG;
using loader::DEBUG;
using std::string;
using std::vector;
using stuff::memory::readMem;
using stuff::memory::writeMem;

typedef void(__fastcall* PointerBiConsumer)(long long, long long);

intptr_t mhw = 0x140000000;

vector<intptr_t> subtitle_setting{ 0x5073E80, 0x10A };
vector<intptr_t> subtitle_show{ 0x5224B80, 0x13e20, 0x332c };
vector<intptr_t> hud_settings{ 0x5073E80, 0xa8, 0x151F8C };

long long xor_settings = 0x0001000001000101;

bool SelectPressed = false;
bool L1Pressed = false;

void toggleSubtitles() {

    bool subs_setting;
    readMem(mhw, subtitle_setting, subs_setting);
    subs_setting ^= true;
    writeMem(mhw, subtitle_setting, subs_setting);

    bool subs_show;
    readMem(mhw, subtitle_show, subs_show);
    subs_show ^= true;
    writeMem(mhw, subtitle_show, subs_show);
}

void toggleHUD() {
    long long hud;
    auto hudAddr = readMem(mhw, hud_settings, hud);
    LOG(DEBUG) << std::hex << "Before @ 0x" << hudAddr << ": " << hud;
    hud ^= xor_settings;
    writeMem(mhw, hud_settings, hud);
    LOG(DEBUG) << std::hex << "After @ 0x" << hudAddr << ": " << hud;
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

CreateHook((PointerBiConsumer)0x1418e8ea0, PollCtrlHook, void, long long p1, long long p2) {
    original(p1, p2);

    Gamepad* gamepad = (Gamepad*)p1;
    if (btnPressed(Button::Select, SelectPressed, gamepad->buttons) == PRESSED) {
        LOG(DEBUG) << std::hex << "Toggle Subtitles: " << Buttons[Button::Select];
        toggleSubtitles();
    }
    auto l1 = btnPressed(Button::L1, L1Pressed, gamepad->buttons);
    if (l1 == PRESSED) {
        LOG(DEBUG) << std::hex << "HUD On: " << Buttons[Button::L1];
        toggleHUD();
    } else if(l1 == RELEASED) {
        LOG(DEBUG) << "HUD Off";
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
