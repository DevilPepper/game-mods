#pragma once

#include <Windows.h>

#include <functional>
#include <tuple>
#include <vector>

#include "function/function.h"

using namespace stuff::functions;

using std::function;

namespace stuff {
  namespace hook {
    class Line {
     private:
      std::vector<std::pair<intptr_t, intptr_t>> hooks;

     public:
      Line();

      Line& init();

      template <class R, class F, class... Args>
      Line& queueHook(intptr_t targetAddr, function<R(F*, Args...)> detour) {
        hooks.push_back({ targetAddr, nullptr });
        auto original = (F*)(&hooks.back().second);
        auto hook = [original](Args... args) -> R { return detour(original, &args...); };
        QueueHook(targetAddr, hook, original);
        return *this;
      }

      template <class F, class... Args>
      Line& queueHook(intptr_t targetAddr, function<void(F*, Args...)> detour) {
        hooks.push_back({ targetAddr, nullptr });
        auto original = (F*)(&hooks.back().second);
        auto hook = [original](Args... args) { detour(original, &args...); };
        QueueHook(targetAddr, hook, original);
        return *this;
      }

      void applyQueued();
      void undoHooks();
    };
  }  // namespace hook
}  // namespace stuff
