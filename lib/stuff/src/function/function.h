#pragma once

#include <Windows.h>

namespace stuff {
  namespace functions {
    typedef void(__fastcall* PointerConsumer)(uintptr_t);
    typedef void(__fastcall* PointerBiConsumer)(long long, long long);
    typedef void(__fastcall* PtrPtrCharCharConsumer)(uintptr_t, uintptr_t, char, char);
    void QueueHook(LPVOID pTarget, LPVOID pDetour, LPVOID* ppOriginal);

    template <typename T>
    void QueueHook(intptr_t pTarget, LPVOID pDetour, T** ppOriginal) {
      QueueHook((LPVOID)pTarget, pDetour, reinterpret_cast<LPVOID*>(ppOriginal));
    }
  }  // namespace functions
}  // namespace stuff
