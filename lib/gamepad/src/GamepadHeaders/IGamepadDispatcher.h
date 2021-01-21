#pragma once

#ifdef GAMEPAD_LISTENER_IMP
#define GPL_DLL __declspec(dllexport)
#else
#define GPL_DLL __declspec(dllimport)
#endif

#include <functional>

#include "GamepadStruct.h"

namespace gamepad {
  using GamepadCallback = std::function<void(const Gamepad&)>;

  class IGamepadDispatcher {
   public:
    virtual IGamepadDispatcher& registerCallback(GamepadCallback callback) = 0;
    virtual IGamepadDispatcher& unregisterCallback(GamepadCallback callback) = 0;
    virtual void update(Gamepad input) = 0;
  };

  GPL_DLL IGamepadDispatcher& GetDispatcher();
}  // namespace gamepad
