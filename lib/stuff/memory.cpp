// stuff.cpp : Defines the functions for the static library.
//
#include "pch.h"
#include "framework.h"

#include "memory.h"
#include<iostream>


using namespace std;

namespace stuff {
    namespace memory {
        intptr_t readMem(HANDLE proc, intptr_t base, vector<intptr_t>& offsets, LPVOID buffer, SIZE_T size) {
            intptr_t addy = base;
            int i = 0;
            for (; i < offsets.size() - 1; i++) {
                ReadProcessMemory(proc, (LPVOID)(addy + offsets[i]), &addy, sizeof(intptr_t), NULL);
            }
            addy += offsets[i];
            ReadProcessMemory(proc, (LPVOID)(addy), buffer, size, NULL);
            return addy;
        }

        intptr_t writeMem(HANDLE proc, intptr_t base, vector<intptr_t>& offsets, LPVOID buffer, SIZE_T size) {
            intptr_t addy = base;
            int i = 0;
            for (; i < offsets.size() - 1; i++) {
                ReadProcessMemory(proc, (LPVOID)(addy + offsets[i]), &addy, sizeof(intptr_t), NULL);
            }
            addy += offsets[i];
            WriteProcessMemory(proc, (LPVOID)(addy), buffer, size, NULL);
            return addy;
        }

        void Helper::setProc(string exe) {
            auto hGameWindow = FindWindow(NULL, exe.c_str());
            DWORD pid = NULL;
            GetWindowThreadProcessId(hGameWindow, &pid);

            proc = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
        }

        Helper::Helper(string exe) : base(0) {
            setProc(exe);
        }
        Helper::Helper(string exe, intptr_t base) : base(base) {
            setProc(exe);
        }

        intptr_t Helper::readMem(vector<intptr_t>& offsets, LPVOID buffer, SIZE_T size) {
            cout << std::hex << proc << "|" << base;
            return stuff::memory::readMem(proc, base, offsets, buffer, size);
        }
        intptr_t Helper::writeMem(vector<intptr_t>& offsets, LPVOID buffer, SIZE_T size) {
            return stuff::memory::writeMem(proc, base, offsets, buffer, size);
        }

        void Helper::readMem(intptr_t address, LPVOID buffer, SIZE_T size) {
            ReadProcessMemory(proc, (LPVOID)address, buffer, size, NULL);
        }
        void Helper::writeMem(intptr_t address, LPVOID buffer, SIZE_T size) {
            WriteProcessMemory(proc, (LPVOID)address, buffer, size, NULL);
        }
        intptr_t Helper::readMemNoBase(vector<intptr_t>& offsets, LPVOID buffer, SIZE_T size) {
            return stuff::memory::readMem(proc, 0, offsets, buffer, size);
        }
        intptr_t Helper::writeMemNoBase(vector<intptr_t>& offsets, LPVOID buffer, SIZE_T size) {
            return stuff::memory::writeMem(proc, 0, offsets, buffer, size);
        }
    }
}