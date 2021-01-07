#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include "MinHook.h"

using std::vector;
using std::string;

namespace stuff {
	namespace memory {
        intptr_t followPointers(intptr_t base, vector<intptr_t>& offsets);
        template<typename T>
        intptr_t readMem(intptr_t base, vector<intptr_t>& offsets, T& buffer) {
            auto addy = followPointers(base, offsets);
            buffer = *(T*)addy;
            return addy;
        }
        template<typename T>
        intptr_t writeMem(intptr_t base, vector<intptr_t>& offsets, T& buffer) {
            auto addy = followPointers(base, offsets);
            *(T*)addy = buffer;
            return addy;
        }
	}
}
