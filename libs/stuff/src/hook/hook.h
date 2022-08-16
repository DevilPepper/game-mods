#pragma once

#include <Windows.h>

namespace stuff {
  namespace hook {
    void init();

    void queue(LPVOID pTarget, LPVOID pDetour, LPVOID* ppOriginal);

    template <typename T>
    void queue(intptr_t pTarget, LPVOID pDetour, T** ppOriginal) {
      queue((LPVOID)pTarget, pDetour, reinterpret_cast<LPVOID*>(ppOriginal));
    }

    void apply();
    void unhook();
  }  // namespace hook
}  // namespace stuff
