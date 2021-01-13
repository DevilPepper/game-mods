#include "MinHook.h"
#include "function.h"

namespace stuff {
  namespace functions {
    void QueueHook(LPVOID pTarget, LPVOID pDetour, LPVOID* ppOriginal) {
      MH_CreateHook((LPVOID)pTarget, pDetour, ppOriginal);
      MH_QueueEnableHook((LPVOID)pTarget);
    }
  }  // namespace functions
}  // namespace stuff
