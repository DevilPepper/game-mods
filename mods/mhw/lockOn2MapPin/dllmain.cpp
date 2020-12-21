// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <optional>
#include <string>
#include <algorithm>

#include "mhw_functions.h"

#include "loader.h"
#include "util.h"

#include "../stuff/stuff.h"

using loader::LOG;
using loader::DEBUG;
using loader::WARN;
using std::vector;
using std::optional;
using std::string;
using MHW::Targets::pinMap;

vector<intptr_t> lockOnOffsets{ 0x05073EC0, 0x50, 0x80, 0x80, -0x7C };
vector<intptr_t> unknown{ 0x5224B80, 0x13FA0 };
vector<intptr_t> lastMonster{ 0x5183DF0, 0x698, 0, 0x138 };
vector<intptr_t> numMonsters{ 0x05073EC0, 0x50, 0x80, 0x80, 0x120, 0x958 };
vector<intptr_t> nonZero{ 0x5073DA0, 0x128 };
vector<intptr_t> pinnedMonsterPtr{ 0x5073DA0, 0x148 };

optional<stuff::memory::Helper> mhw;

bool isOnTheLoose(intptr_t monsterAddr) {
    // Shameless copy and paste from Hunter Pie    
    monsterAddr += 0x61C8;
    int actionId = -1;

    mhw->readMem(monsterAddr + 0xB0, &actionId, sizeof(int));
    LOG(WARN) << std::hex << "actionId @ 0x" << (monsterAddr + 0xB0) << ": " << actionId;

    vector<intptr_t> monsterAction{
        monsterAddr + (2*8) + 0x68,
        (intptr_t)actionId * 8,
        0,
        0x20
    };

    intptr_t actionPtr = NULL;
    unsigned int offset = 0;

    auto actionAddr = mhw->readMemNoBase(monsterAction, &actionPtr, sizeof(intptr_t));
    LOG(WARN) << std::hex << "monster action @ 0x" << actionAddr << ": " << actionPtr;
    mhw->readMem(actionPtr + 3, &offset, sizeof(unsigned int));
    LOG(WARN) << std::hex << "action offset @ 0x" << (actionPtr + 3) << ": " << offset;

    vector<intptr_t> actionRef{ actionPtr + offset + 7 + 8, 0 };

    char actionString[65];
    actionString[64] = 0;
    auto strAddr = mhw->readMemNoBase(actionRef, actionString, 64);
    string action(actionString);
    LOG(WARN) << std::hex << "action string @ 0x" << strAddr << ": " << actionString << "...toString(): " << action;

    return  action.find("Capture") == string::npos
        && (action.find("Die") == string::npos || action.find("DieSleep") != string::npos)
        && (action.find("Dead") == string::npos || action.find("Deadly") != string::npos);
}

int getRealIndex(intptr_t address, int idx) {
    address -= 0x19F8;
    mhw->readMem(address + ((intptr_t)idx*8), &idx, sizeof(int));
    return idx;
}

void lockOn2MapPin() {
    int idx = -1;
    auto lockOnAddr = mhw->readMem(lockOnOffsets, &idx, sizeof(int));
    LOG(WARN) << std::hex << "lockOn @ 0x" << lockOnAddr << ": " << idx;

    uintptr_t p0 = 0;
    auto unknownAddr = mhw->readMem(unknown, &p0, sizeof(uintptr_t));
    LOG(WARN) << std::hex << "p0 @ 0x" << unknownAddr << ": " << p0;

    uintptr_t monster = 0;
    if (idx != -1) {
        int nMonsters = -1;
        auto numMonstersAddr = mhw->readMem(numMonsters, &nMonsters, sizeof(int));
        LOG(WARN) << std::hex << "numMonsters @ 0x" << numMonstersAddr << ": " << nMonsters;

        if (nMonsters > 0) {
            vector<uintptr_t> monsters;
            nMonsters--;
            for (int i = 0; i <= nMonsters; i++) {
                auto offset = (nMonsters - i) * 8;
                auto monster_i = lastMonster;
                monster_i[2] = offset;
                auto monsterAddr = mhw->readMem(monster_i, &monster, sizeof(uintptr_t));
                LOG(WARN) << std::hex << "monster found @ 0x" << monsterAddr << ": " << monster;
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
        auto nonZeroAddr = mhw->readMem(nonZero, &monster, sizeof(uintptr_t));
        LOG(WARN) << std::hex << "non-zero @ 0x" << nonZeroAddr << ": " << monster;

        if (monster != 0) {
            auto pinnedMonsterAddr = mhw->readMem(pinnedMonsterPtr, &monster, sizeof(uintptr_t));
            LOG(WARN) << std::hex << "pinned monster @ 0x" << pinnedMonsterAddr << ": " << monster;
            pinMap(p0, monster, 1);
        }
    }
}

CreateHook(MHW::Targets::lockOnInc, LockOnIncHook, void, uintptr_t ptr) {
    original(ptr);
    if (!mhw) {
        mhw = stuff::memory::Helper("MONSTER HUNTER: WORLD(421409)", 0x140000000);
    }
    lockOn2MapPin();
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
        QueueHook(LockOnIncHook);
        MH_ApplyQueued();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

