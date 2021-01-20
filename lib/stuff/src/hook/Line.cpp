#include "Line.h"

#include <MinHook.h>

namespace stuff {
  namespace hook {
    Line::Line() : hooks(std::vector<std::pair<intptr_t, intptr_t>>()) {}
    Line& Line::init() {
      MH_Initialize();
      return *this;
    }
    void Line::applyQueued() {
      MH_ApplyQueued();
    }
    void Line::undoHooks() {
      MH_Initialize();
      for (auto& hook : hooks) {
        MH_QueueDisableHook((LPVOID)hook.first);
      }
      MH_ApplyQueued();
    }
  }  // namespace hook
}  // namespace stuff
