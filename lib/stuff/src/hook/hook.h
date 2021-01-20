#pragma once

#include <Windows.h>

#include <vector>

namespace stuff {
  namespace hook {
    void init();

    void queue(LPVOID pTarget, LPVOID pDetour, LPVOID* ppOriginal);

    template <typename T>
    void queue(intptr_t pTarget, LPVOID pDetour, T** ppOriginal) {
      queue((LPVOID)pTarget, pDetour, reinterpret_cast<LPVOID*>(ppOriginal));
    }

    template <typename T>
    void queue(intptr_t pTarget, LPVOID pDetour, T** ppOriginal, std::vector<intptr_t>& targets) {
      targets.push_back(pTarget);
      queue((LPVOID)pTarget, pDetour, reinterpret_cast<LPVOID*>(ppOriginal));
    }

    void apply();
    void unhook(std::vector<intptr_t>& targets);
  }  // namespace hook
}  // namespace stuff
