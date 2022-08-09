#pragma once

#include <list>

#include "GamepadStruct.h"
#include "IGamepadDispatcher.h"

namespace gamepad {
  class GamepadDispatcher : public IGamepadDispatcher {
   private:
    std::list<GamepadCallback> callbacks;

   public:
    GamepadDispatcher();
    GamepadToken registerCallback(GamepadCallback callback);
    IGamepadDispatcher& unregisterCallback(GamepadToken callback);

    IGamepadDispatcher& registerCallback(GamepadCallback callback, GamepadTokens& tokens);
    void unregisterCallback(GamepadTokens& tokens);

    void update(Gamepad input);
  };
}  // namespace gamepad
