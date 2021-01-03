// dllmain.cpp : Defines the entry point for the DLL application.
#include <future>
#include <thread>
#include <chrono>

#include <windows.h>;

#include "loader.h"
#include "util.h"
#include "ghidra_export.h"

// There has to be a better way
#include "../stuff/stuff.h"

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

typedef HRESULT(__fastcall* CreateDevice)(REFGUID, LPDIRECTINPUTDEVICE*, LPUNKNOWN);
CreateDevice fnCreateDevice = nullptr;

IDirectInput8* device = nullptr;
vector<LPDIRECTINPUTDEVICE8> gamepads;
unsigned char gInput[32];

LPDIRECTINPUTDEVICE8 kb = nullptr;
LPDIRECTINPUTDEVICE8 mouse = nullptr;
std::future<void> ctrlThread;

HANDLE procHandle = NULL;
// TODO: Doesn't work. Need to unprotect memory...
intptr_t mhw = 0x140000000;

vector<intptr_t> subtitle_setting{ 0x5073E70, 0x10A };
vector<intptr_t> subtitle_show{ 0x5224B80, 0x13e20, 0x332c };
vector<intptr_t> hud_settings{ 0x5073E70, 0xa8, 0x151F8C };

long long xor_settings = 0x0001000001000101;

void setHandle() {
    auto hGameWindow = FindWindow(NULL, "MONSTER HUNTER: WORLD(421409)");
    DWORD pid = NULL;
    GetWindowThreadProcessId(hGameWindow, &pid);

    procHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
}

HRESULT CreateDeviceHook(
    REFGUID rguid,
    LPDIRECTINPUTDEVICE* lplpDirectInputDevice,
    LPUNKNOWN pUnkOuter
) {
    // TODO: start thread here
    LOG(DEBUG) << "Starting thread";
    return fnCreateDevice(rguid, lplpDirectInputDevice, pUnkOuter);
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

BTN_ACTION btnPressed(int btn, bool& pressed, unsigned char input[32]) {
    if ((int)input[btn] == 0x80) {
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

BOOL enumerateGameControllers(LPCDIDEVICEINSTANCE devInst, LPVOID devPtr)
{
    LPDIRECTINPUTDEVICE8 gamepad = nullptr;
    if (FAILED(device->CreateDevice(devInst->guidInstance, &gamepad, NULL)))
    {
        LOG(ERR) << "Failed to get device " << devInst->tszProductName << " - " << devInst->tszInstanceName;
    }
    else
    {
        gamepads.push_back(gamepad);
        //gamepad->SetCooperativeLevel(hGameWindow, DISCL_BACKGROUND | DISCL_EXCLUSIVE);
        gamepad->SetDataFormat(&c_dfDIJoystick);

        LOG(DEBUG) << "Got device " << devInst->tszProductName << " - " << devInst->tszInstanceName;
    }
    return DIENUM_CONTINUE;
}

void getGamepads() {
    if (device->EnumDevices(DI8DEVCLASS_GAMECTRL, &enumerateGameControllers, device, DIEDFL_ATTACHEDONLY) != DI_OK) {
        LOG(DEBUG) << "Can't find gamepad";
        device->Release();
    }
    //gamepad->Acquire();
}

void getInput() {
    memset(gInput, 0, 32);
    DIJOYSTATE gamepadState;
    for (auto gamepad : gamepads) {
        if (FAILED(gamepad->Poll())) {
            gamepad->Acquire();
        }
        else {
            gamepad->GetDeviceState(sizeof(DIJOYSTATE), &gamepadState);
            for (int i = 0; i < 32; i++) {
                gInput[i] |= gamepadState.rgbButtons[i];
            }
        }
    }
}

void sleep() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void gamepadLoop() {
    bool Select = false;
    bool L1 = false;

    if (procHandle == NULL) {
        setHandle();
    }

    while (gamepads.size() == 0) {
        getGamepads();
        sleep();
    }

    while (gamepads.size() > 0) {
        getInput();
        if (btnPressed(6, Select, gInput) == PRESSED) {
            toggleSubtitles();
        }
        auto l1 = btnPressed(4, L1, gInput);
        if (l1 == PRESSED) {
            toggleHUD();
        } else if(l1 == RELEASED) {
            toggleHUD();
        }
        sleep();
    }
    LOG(ERR) << "Terminating... Not checking user input anymore!";
}

int createDevicesAndHook() {
    HINSTANCE hInst = (HINSTANCE)GetModuleHandle("MonsterHunterWorld.exe");
    LOG(DEBUG) << "DInput Got";
    if (DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&device, NULL) != DI_OK)
    {
        LOG(ERR) << "Failed to acquire DirectInput handle";
        return -1;
    }

    return 0;
}

CreateHook(MH::File::LoadResource, StartGamepadThread, void*, void* fileMgr,
    void* objDef, char* filename, int flag) {
    void* object = original(fileMgr, objDef, filename, flag);
    if (flag == 1 && objDef == MH::Quest::QuestNoList::ResourcePtr) {
        if (!ctrlThread.valid()) {
            LOG(DEBUG) << "Starting user input thread...";
            ctrlThread = std::async(std::launch::async, gamepadLoop);
        }
    }
    return object;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        createDevicesAndHook();
        MH_Initialize();
        QueueHook(StartGamepadThread);
        MH_ApplyQueued();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
