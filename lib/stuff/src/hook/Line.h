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

      template <class R, class... Args>
      Line& queueHook(intptr_t targetAddr, function<R(function<R(Args...)>*, Args...)> detour) {
        hooks.push_back({ targetAddr, nullptr });
        auto original = (function<R(Args...)>*)(&hooks.back().second);
        auto hook = [original](Args... args) -> R { return detour(original, &args...); };
        QueueHook(targetAddr, hook, original);
        return *this;
      }

      template <class... Args>
      Line& queueHook(intptr_t targetAddr,
                      function<void(function<void(Args...)>*, Args...)> detour) {
        hooks.push_back({ targetAddr, nullptr });
        auto original = (function<void(Args...)>*)(&hooks.back().second);
        auto hook = [original](Args... args) -> void { detour(original, &args...); };
        QueueHook(targetAddr, hook, original);
        return *this;
      }

      void applyQueued();
      void undoHooks();
    };
  }  // namespace hook
}  // namespace stuff
