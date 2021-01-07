// dllmain.cpp : Defines the entry point for the DLL application.
// #include <functional>
#include <future>
#include <thread>
#include <chrono>

#include <windows.h>

#include "loader.h"
#pragma comment (lib, "loader.lib")

#include "stuff.h"
#pragma comment (lib, "stuff.lib")

using loader::LOG;
using loader::DEBUG;
using std::string;
using std::vector;
using stuff::memory::readMem;
using stuff::memory::writeMem;
using stuff::json::parseHexString;
using stuff::json::parseHexStrings;

using namespace stuff::functions;

PointerBiConsumer original = nullptr;
intptr_t PollCtrl;

Button HUDToggle = Button::L1;
Button SubtitlesToggle = Button::Select;

intptr_t mhw = 0x140000000;

vector<intptr_t> subtitle_setting;
vector<intptr_t> subtitle_show;
vector<intptr_t> hud_settings;

bool toggles[8];

void loadAddresses() {
    auto addys = stuff::json::loadAddresses();
    subtitle_setting = parseHexStrings(addys["subtitle_setting"]);
    subtitle_show    = parseHexStrings(addys["subtitle_show"]);
    hud_settings     = parseHexStrings(addys["hud_settings"]);
    PollCtrl         = parseHexString(addys["PollController()"]);
}

void loadConfig() {
    // TODO: get this tf outta here
    vector<string> toggleStr {
        "Player Info",
        "Partner Info",
        "Scoutfly Notifications",
        "Minimap",
        "Large Monster Icon",
        "Button Guide",
        "Objectives",
        "Slinger Display",
        "Item Bar"
    };
    auto settings = stuff::json::loadConfig("HUD_toggles.json");
    for (int i=0; i<8; i++) {
        toggles[i] = settings[toggleStr[i]].get<bool>();
    }
}

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
    hud ^= *reinterpret_cast<long long*>(toggles);
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

void PollCtrlHook(long long p1, long long p2) {
    original(p1, p2);

    Gamepad* gamepad = (Gamepad*)p1;
    if (btnPressed(SubtitlesToggle, SelectPressed, gamepad->buttons) == PRESSED) {
        LOG(DEBUG) << std::hex << "Toggle Subtitles: " << Buttons[SubtitlesToggle];
        toggleSubtitles();
    }
    auto l1 = btnPressed(HUDToggle, L1Pressed, gamepad->buttons);
    if (l1 == PRESSED) {
        LOG(DEBUG) << std::hex << "HUD On: " << Buttons[HUDToggle];
        toggleHUD();
    } else if(l1 == RELEASED) {
        LOG(DEBUG) << "HUD Off";
        toggleHUD();
    }
   return;
}

void hookem() {
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
    case DLL_PROCESS_ATTACH:
        loadAddresses();
        loadConfig();
        hookem();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
