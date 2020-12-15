// dllmain.cpp : Defines the entry point for the DLL application.
#include <future>
#include <thread>
#include <chrono>

#include "loader.h"
#include "util.h"
#include "ghidra_export.h"

#define DIRECTINPUT_VERSION 0x0800
#include <Windows.h>
#include <dinput.h>

#include <detours\detours.h>

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
//5073E70
using loader::LOG;
using loader::DEBUG;
using loader::ERR;
using std::string;
using std::vector;

typedef HRESULT(__fastcall* CreateDevice)(REFGUID, LPDIRECTINPUTDEVICE*, LPUNKNOWN);
CreateDevice fnCreateDevice = nullptr;

LPDIRECTINPUTDEVICE8 gamepad = nullptr;
LPDIRECTINPUTDEVICE8 kb = nullptr;
LPDIRECTINPUTDEVICE8 mouse = nullptr;
std::future<void> ctrlThread;

HANDLE procHandle = NULL;
// TODO: Doesn't work. Need to unprotect memory...
intptr_t mhw = 0x140000000;

vector<intptr_t> subtitle_setting{ 0x5073E70, 0x10A };
vector<intptr_t> subtitle_show{ 0x5224B80, 0x13e20, 0x332c };
vector<intptr_t> hud_settings{ 0x5073E70, 0xa8, 0x151F8C };

//long long xor_settings = 0x0101000100000100;
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

void readMem(HANDLE proc, intptr_t base, vector<intptr_t>& offsets, LPVOID buffer, SIZE_T size) {
    intptr_t addy = base;
    int i = 0;
    for (; i < offsets.size() - 1; i++) {
        ReadProcessMemory(proc, (LPVOID)(addy + offsets[i]), &addy, sizeof(intptr_t), NULL);
    }
    ReadProcessMemory(proc, (LPVOID)(addy + offsets[i]), buffer, size, NULL);
}

void writeMem(HANDLE proc, intptr_t base, vector<intptr_t>& offsets, LPVOID buffer, SIZE_T size) {
    intptr_t addy = base;
    int i = 0;
    for (; i < offsets.size() - 1; i++) {
        ReadProcessMemory(proc, (LPVOID)(addy + offsets[i]), &addy, sizeof(intptr_t), NULL);
    }
    LOG(DEBUG) << std::hex << "Writing @ 0x" << addy + offsets[i];
    WriteProcessMemory(proc, (LPVOID)(addy + offsets[i]), buffer, size, NULL);
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

BTN_ACTION btnPressed(int btn, bool& pressed, DIJOYSTATE& state) {
    if ((int)state.rgbButtons[btn] == 0x80) {
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

bool btnHeld(int btn, DIJOYSTATE& state) {
    return (int)state.rgbButtons[btn] == 0x80;
}

void testFunc() {
    DIJOYSTATE gamepadState;
    bool Select = false;
    bool L1 = false;

    if (procHandle == NULL) {
        setHandle();
    }

    while (gamepad != nullptr) {
        if (FAILED(gamepad->Poll())) {
            gamepad->Acquire();
        }
        else {
            gamepad->GetDeviceState(sizeof(DIJOYSTATE), &gamepadState);

            if (btnPressed(6, Select, gamepadState) == PRESSED) {
                toggleSubtitles();
            }
            auto l1 = btnPressed(4, L1, gamepadState);
            if (l1 == PRESSED) {
                toggleHUD();
            } else if(l1 == RELEASED) {
                toggleHUD();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    LOG(ERR) << "Terminating... Not checking user input anymore!";
}


CreateHook(MH::File::LoadResource, StartGamepadThread, void*, void* fileMgr,
    void* objDef, char* filename, int flag) {
    void* object = original(fileMgr, objDef, filename, flag);
    if (flag == 1 && objDef == MH::Quest::QuestNoList::ResourcePtr) {
        if (!ctrlThread.valid()) {
            LOG(DEBUG) << "Starting user input thread...";
            ctrlThread = std::async(std::launch::async, testFunc);
        }
    }
    return object;
}

void* hookVTable(void* pVTable, int nOffset, PVOID detour, string fnName) {
    auto ptrVtable = *((intptr_t*)pVTable);
    auto ptrFunction = ptrVtable + sizeof(intptr_t) * nOffset;
    auto ptrOriginal = *((intptr_t*)ptrFunction);

    LOG(DEBUG) << "VTable containing pointer to" << fnName << "(): " << std::hex << ptrVtable;
    LOG(DEBUG) << std::hex 
               << "Hooking " << fnName << "() @ 0x" << ptrOriginal
               << "with hook function at @ 0x" << detour;

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)ptrOriginal, detour);
    DetourTransactionCommit();

    return (void*)ptrOriginal;
}
void* hookVTable(void* pVTable, int nOffset, PVOID detour) {
    return hookVTable(pVTable, nOffset, detour, "OriginalFunction");
}

BOOL enumerateGameControllers(LPCDIDEVICEINSTANCE devInst, LPVOID devPtr)
{
    auto device = (IDirectInput8*)devPtr;
    if (FAILED(device->CreateDevice(devInst->guidInstance, &gamepad, NULL)))
    {
        LOG(ERR) << "Failed to get device " << devInst->tszProductName << " - " << devInst->tszInstanceName;
    }
    else
    {
        LOG(DEBUG) << "Got device " << devInst->tszProductName << " - " << devInst->tszInstanceName;
    }
    return DIENUM_CONTINUE;
}

int createDevicesAndHook() {
    IDirectInput8* device = nullptr;
    HINSTANCE hInst = (HINSTANCE)GetModuleHandle("MonsterHunterWorld.exe");
    LOG(DEBUG) << "DInput Got";
    if (DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&device, NULL) != DI_OK)
    {
        LOG(ERR) << "Failed to acquire DirectInput handle";
        return -1;
    }
    //if (device->CreateDevice(GUID_SysKeyboard, &kb, NULL) != DI_OK)
    //{
    //    LOG(DEBUG) << "Can't find keyboard";
    //    device->Release();
    //    return -1;
    //}
    //if (device->CreateDevice(GUID_SysMouse, &mouse, NULL) != DI_OK)
    //{
    //    LOG(DEBUG) << "Can't find mouse";
    //    device->Release();
    //    return -1;
    //}
    
    LOG(DEBUG) << "Enum Devices";

    if (device->EnumDevices(DI8DEVCLASS_GAMECTRL, &enumerateGameControllers, device, DIEDFL_ATTACHEDONLY) != DI_OK) {
        LOG(DEBUG) << "Can't find gamepad";
        device->Release();
        return -1;
    }

    //gamepad->SetCooperativeLevel(hGameWindow, DISCL_BACKGROUND | DISCL_EXCLUSIVE);
    //kb->Acquire();
    //mouse->Acquire();

    LOG(DEBUG) << "Set Ctrl data";
    gamepad->SetDataFormat(&c_dfDIJoystick);
    LOG(DEBUG) << "Aquire Ctrl";

    //gamepad->Acquire();
    // maybe hook to MH::File::LoadResource
    //fnCreateDevice = (CreateDevice)hookVTable(device, 2, CreateDeviceHook, "CreateDeviceHook");
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        LOG(DEBUG) << "create devices";
        createDevicesAndHook();
        LOG(DEBUG) << "hook fn";
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

