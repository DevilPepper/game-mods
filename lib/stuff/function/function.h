#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include "MinHook.h"

using std::vector;
using std::string;

namespace stuff {
	namespace functions {
	    typedef void(__fastcall* PointerConsumer)(uintptr_t);
        typedef void(__fastcall* PointerBiConsumer)(long long, long long);
		typedef void(__fastcall* PtrPtrCharCharConsumer)(uintptr_t, uintptr_t, char, char);
        
        template<typename T>
        void QueueHook(intptr_t pTarget, LPVOID pDetour, T** ppOriginal) {
            MH_CreateHook((LPVOID)pTarget, pDetour, reinterpret_cast<LPVOID*>(ppOriginal));
            MH_QueueEnableHook((LPVOID)pTarget);
        }
	}
}
