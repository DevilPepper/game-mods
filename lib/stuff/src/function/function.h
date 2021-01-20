#pragma once

#include <Windows.h>

namespace stuff {
  namespace functions {
    typedef void(__fastcall* PointerConsumer)(uintptr_t);
    typedef void(__fastcall* PointerBiConsumer)(long long, long long);
    typedef void(__fastcall* PtrPtrCharCharConsumer)(uintptr_t, uintptr_t, char, char);
  }  // namespace functions
}  // namespace stuff
