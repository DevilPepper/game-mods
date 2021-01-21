#pragma once

#include <functional>
#include <vector>

#include "GamepadStruct.h"
#include "IGamepadDispatcher.h"

namespace gamepad {
  class GamepadDispatcher : public IGamepadDispatcher {
   private:
    std::vector<GamepadCallback> callbacks;

   public:
    GamepadDispatcher();
    IGamepadDispatcher& registerCallback(GamepadCallback callback);
    IGamepadDispatcher& unregisterCallback(GamepadCallback callback);
    void update(Gamepad input);
  };
}  // namespace gamepad
