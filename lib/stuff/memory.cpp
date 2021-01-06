// stuff.cpp : Defines the functions for the static library.
//
#include "pch.h"
#include "framework.h"

#include "memory.h"
#include<iostream>


using namespace std;

namespace stuff {
    namespace memory {
        intptr_t followPointers(intptr_t base, vector<intptr_t>& offsets) {
            auto addy = base;
            int i = 0;
            for (; i < offsets.size() - 1; i++) {
                addy = *(intptr_t*)(addy + offsets[i]);
            }
            addy += offsets[i];
            return addy;
        }
    }
}
