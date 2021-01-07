// dllmain.cpp : Defines the entry point for the DLL application.
#include <optional>
#include <string>
#include <algorithm>

#include "loader.h"
#pragma comment (lib, "loader.lib")

#include "stuff.h"
#pragma comment (lib, "stuff.lib")

using loader::LOG;
using loader::DEBUG;
using std::vector;
using std::string;

using namespace stuff::memory;
using stuff::json::parseHexString;
using stuff::json::parseHexStrings;

using namespace stuff::functions;

vector<intptr_t> lockOnOffsets;
vector<intptr_t> unknown;
vector<intptr_t> lastMonster;
vector<intptr_t> numMonsters;
vector<intptr_t> nonZero;
vector<intptr_t> pinnedMonsterPtr;

intptr_t mhw = 0x140000000;

PtrPtrCharCharConsumer PinMapActual = nullptr;

PointerConsumer original = nullptr;
intptr_t LockOnInc;

void loadAddresses() {
    auto addys = stuff::json::loadAddresses();
    lockOnOffsets    = parseHexStrings(addys["lockOnOffsets"]);
    unknown          = parseHexStrings(addys["unknown"]);
    lastMonster      = parseHexStrings(addys["lastMonster"]);
    numMonsters      = parseHexStrings(addys["numMonsters"]);
    nonZero          = parseHexStrings(addys["nonZero"]);
    pinnedMonsterPtr = parseHexStrings(addys["pinnedMonsterPtr"]);

    PinMapActual     = (PtrPtrCharCharConsumer)parseHexString(addys["PinMap()"]);
    LockOnInc        = parseHexString(addys["LockOnIncrement()"]);
}

void pinMap(uintptr_t unknown, uintptr_t target, char isMonster) {
    PinMapActual(unknown, target, isMonster, 0);
}

bool isOnTheLoose(intptr_t monsterAddr) {
    // Shameless copy and paste from Hunter Pie    
    monsterAddr += 0x61C8;
    int actionId = *(int*)(monsterAddr + 0xB0);

    LOG(DEBUG) << std::hex << "actionId @ 0x" << (monsterAddr + 0xB0) << ": " << actionId;

    vector<intptr_t> monsterAction{
        monsterAddr + (2*8) + 0x68,
        (intptr_t)actionId * 8,
        0,
        0x20
    };

    intptr_t actionPtr = NULL;
    auto actionAddr = readMem(0, monsterAction, actionPtr);
    LOG(DEBUG) << std::hex << "monster action @ 0x" << actionAddr << ": " << actionPtr;
    
    auto offset = *(unsigned int*)(actionPtr + 3);
    LOG(DEBUG) << std::hex << "action offset @ 0x" << (actionPtr + 3) << ": " << offset;

    vector<intptr_t> actionRef{ actionPtr + offset + 7 + 8, 0 };

    auto strAddr = (char*)followPointers(0, actionRef);
    string action(strAddr);

    LOG(DEBUG) << std::hex << "action string @ 0x" << strAddr << ": " << action;

    return  action.find("Capture") == string::npos
        && (action.find("Die") == string::npos || action.find("DieSleep") != string::npos)
        && (action.find("Dead") == string::npos || action.find("Deadly") != string::npos);
}

int getRealIndex(intptr_t address, int idx) {
    address -= 0x19F8;
    return *(int*)(address + ((intptr_t)idx*8));
}

void lockOn2MapPin() {
    int idx = -1;
    auto lockOnAddr = readMem(mhw, lockOnOffsets, idx);
    LOG(DEBUG) << std::hex << "lockOn @ 0x" << lockOnAddr << ": " << idx;

    uintptr_t p0 = 0;
    auto unknownAddr = readMem(mhw, unknown, p0);
    LOG(DEBUG) << std::hex << "p0 @ 0x" << unknownAddr << ": " << p0;

    uintptr_t monster = 0;
    if (idx != -1) {
        int nMonsters = -1;
        auto numMonstersAddr = readMem(mhw, numMonsters, nMonsters);
        LOG(DEBUG) << std::hex << "numMonsters @ 0x" << numMonstersAddr << ": " << nMonsters;

        if (nMonsters > 0) {
            vector<uintptr_t> monsters;
            nMonsters--;
            for (int i = 0; i <= nMonsters; i++) {
                auto offset = (nMonsters - i) * 8;
                auto monster_i = lastMonster;
                monster_i[2] = offset;
                auto monsterAddr = readMem(mhw, monster_i, monster);
                LOG(DEBUG) << std::hex << "monster found @ 0x" << monsterAddr << ": " << monster;
                monsters.push_back(monster);
            }

            // filter out dead or captured monsters that haven't despawned
            vector<uintptr_t> monstersOnTheLoose;
            std::copy_if(monsters.begin(), monsters.end(),
                std::back_inserter(monstersOnTheLoose),
                [](uintptr_t m) {return isOnTheLoose(m);});

            pinMap(p0, monstersOnTheLoose[getRealIndex(lockOnAddr, idx)], 1);
        }
    }
    else {
        auto nonZeroAddr = readMem(mhw, nonZero, monster);
        LOG(DEBUG) << std::hex << "non-zero @ 0x" << nonZeroAddr << ": " << monster;

        if (monster != 0) {
            auto pinnedMonsterAddr = readMem(mhw, pinnedMonsterPtr, monster);
            LOG(DEBUG) << std::hex << "pinned monster @ 0x" << pinnedMonsterAddr << ": " << monster;
            pinMap(p0, monster, 1);
        }
    }
}

void LockOnIncHook(uintptr_t ptr) {
    original(ptr);
    lockOn2MapPin();
}

void hookem() {
    MH_Initialize();
    QueueHook(LockOnInc, &LockOnIncHook, &original);
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
        hookem();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
