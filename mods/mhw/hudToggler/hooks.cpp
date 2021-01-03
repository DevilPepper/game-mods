//
//#include "loader.h"
//#include "util.h"
//
//#define CINTERFACE
//#define DIRECTINPUT_VERSION 0x0800
//#include <Windows.h>
//#include <dinput.h>
//
//#include <detours\detours.h>
//
//#pragma comment (lib, "dinput8.lib")
//#pragma comment (lib, "dxguid.lib")
//
//using namespace loader;
//
//
//typedef HRESULT(WINAPI* DINPUT8CREATE)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);
//DINPUT8CREATE DInput8Create = nullptr;
//
//LPDIRECTINPUTDEVICE8 gameCtrl;
//
//typedef HRESULT(__fastcall* GetDeviceState)(IDirectInputDevice8*, DWORD, LPVOID);
//GetDeviceState fnGetDeviceState = nullptr;
//
//typedef HRESULT(__fastcall* GetDeviceData)(IDirectInputDevice8*, DWORD, LPDIDEVICEOBJECTDATA, LPDWORD, DWORD);
//GetDeviceData fnGetDeviceData = nullptr;
//
//
//BOOL CALLBACK enumerateGameControllers(LPCDIDEVICEINSTANCE devInst, LPVOID pvRef)
//{
//    LOG(ERR) << "Get 'em  Controllers!!";
//    auto ref = (IDirectInput8*)pvRef;
//
//    // create interface for the current game controller
//    if (FAILED(ref->CreateDevice(devInst->guidInstance, &gameCtrl, NULL)))
//        LOG(ERR) << "Not a Controller!!";
//    return DIENUM_CONTINUE;
//
//}
//
//HRESULT __fastcall HookGetDeviceState(IDirectInputDevice8* pThis, DWORD cbData, LPVOID lpvData) {
//    LOG(ERR) << "Get 'em states: " << pThis << "->" << fnGetDeviceState;
//    auto ret = fnGetDeviceState(pThis, cbData, lpvData);
//    LOG(ERR) << "Got 'em states: " << std::hex << ret;
//    /*
//    if (ret == DI_OK)
//    {
//        BYTE* keys = (BYTE*)lpvData;
//        if (keys[DIK_W] == 0x80) {
//            LOG(ERR) << "[W]";
//        } if (keys[DIK_S] == 0x80) {
//            LOG(ERR) << "[S]";
//        } if (keys[DIK_A] == 0x80) {
//            LOG(ERR) << "[A]";
//        } if (keys[DIK_D] == 0x80) {
//            LOG(ERR) << "[D]";
//        }
//    }
//    */
//    return DI_OK;
//}
//
//HRESULT __fastcall GetDeviceDataHook(
//    IDirectInputDevice8* pThis,
//    DWORD cbObjectData,
//    LPDIDEVICEOBJECTDATA rgdod,
//    LPDWORD pdwInOut,
//    DWORD dwFlags
//) {
//    LOG(ERR) << "Get 'em data: " << pThis << "->" << fnGetDeviceState;
//    auto ret = fnGetDeviceData(pThis, cbObjectData, rgdod, pdwInOut, dwFlags);
//    LOG(ERR) << "Got 'em data: " << std::hex << ret;
//
//    return ret;
//}
//
//// By Timb3r
//// Source: https://gamephreakers.com/2018/08/introduction-to-vtable-hooking/
//void* HookVTableFunction(void* pVTable, int nOffset, void* detour)
//{
//    auto ptrVtable = *((intptr_t*)pVTable); // Pointer to our chosen vtable
//    auto ptrFunction = ptrVtable + sizeof(intptr_t) * nOffset; // The offset to the function (remember it's a zero indexed array with a size of four bytes)
//    auto ptrOriginal = *((intptr_t*)ptrFunction); // Save original address
//
//    LOG(ERR) << "vTable: " << std::hex << ptrVtable;
//    LOG(ERR) << "Function pointer: " << std::hex << ptrFunction;
//    LOG(ERR) << "Original Function: " << ptrOriginal;
//    LOG(ERR) << "Hooked Function: " << detour;
//    LOG(ERR) << "size of ptr" << sizeof(intptr_t);
//
//
//    //// Edit the memory protection so we can modify it
//    //MEMORY_BASIC_INFORMATION mbi;
//    //VirtualQuery((LPCVOID)ptrFunction, &mbi, sizeof(mbi));
//    //VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect);
//
//    //*((intptr_t*)ptrFunction) = (intptr_t)detour;
//    ////MH_CreateHook(proc, detour, reinterpret_cast<LPVOID*>(original));
//    ////LOG(ERR) << "Original address: " << original;
//    ////MH_QueueEnableHook(proc);
//    //VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect);
//
//    return (void*)ptrOriginal;
//}
//
//void HookVTableFunction_V2(void* pVTable, int nOffset, LPVOID detour, void* original)
//{
//    auto ptrVtable = *((intptr_t*)pVTable); // Pointer to our chosen vtable
//    auto ptrFunction = ptrVtable + sizeof(intptr_t) * nOffset; // The offset to the function (remember it's a zero indexed array with a size of four bytes)
//    auto ptrOriginal = (void*)(*((intptr_t*)ptrFunction)); // Save original address
//
//    LOG(ERR) << "vTable: " << std::hex << ptrVtable;
//    LOG(ERR) << "Function pointer: " << std::hex << ptrFunction;
//    LOG(ERR) << "Original Function: " << std::hex << ptrOriginal;
//    LOG(ERR) << "Hooked Function: " << detour;
//    LOG(ERR) << "size of ptr" << sizeof(intptr_t);
//
//    MH_Initialize();
//    MH_CreateHook(ptrOriginal, detour, reinterpret_cast<LPVOID*>(original));
//    MH_QueueEnableHook(ptrOriginal);
//    MH_ApplyQueued();
//}
//
//HRESULT WINAPI DirectInput8CreateHook(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter) {
//    auto ret = DInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);
//    IDirectInput8* mainDevice = (IDirectInput8*)ppvOut;
//
//    LOG(ERR) << "Got 'em: " << ppvOut;
//    //EnumDevices(DI8DEVCLASS_GAMECTRL, &enumerateGameControllers, mainDevice, DIEDFL_ATTACHEDONLY);
//   //mainDevice->Release();
//
//    return ret;
//}
//
//void hookController() {
//    char syspath[MAX_PATH];
//    GetSystemDirectory(syspath, _countof(syspath));
//    strcat_s(syspath, "\\dinput8.dll");
//    HMODULE hMod = LoadLibrary(syspath);
//    auto proc = GetProcAddress(hMod, "DirectInput8Create");
//
//    MH_Initialize();
//    MH_CreateHook(proc, &DirectInput8CreateHook, reinterpret_cast<LPVOID*>(&DInput8Create));
//    MH_QueueEnableHook(proc);
//    MH_ApplyQueued();
//}

// void* hookVTable(void* pVTable, int nOffset, PVOID detour, string fnName) {
//     auto ptrVtable = *((intptr_t*)pVTable);
//     auto ptrFunction = ptrVtable + sizeof(intptr_t) * nOffset;
//     auto ptrOriginal = *((intptr_t*)ptrFunction);

//     LOG(DEBUG) << "VTable containing pointer to" << fnName << "(): " << std::hex << ptrVtable;
//     LOG(DEBUG) << std::hex 
//                << "Hooking " << fnName << "() @ 0x" << ptrOriginal
//                << "with hook function at @ 0x" << detour;

//     DetourTransactionBegin();
//     DetourUpdateThread(GetCurrentThread());
//     DetourAttach(&(PVOID&)ptrOriginal, detour);
//     DetourTransactionCommit();

//     return (void*)ptrOriginal;
// }
// void* hookVTable(void* pVTable, int nOffset, PVOID detour) {
//     return hookVTable(pVTable, nOffset, detour, "OriginalFunction");
// }
