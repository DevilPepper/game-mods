#include "GamepadDispatcher.h"

#include <algorithm>
#include <functional>
#include <vector>

namespace gamepad {
  GamepadDispatcher::GamepadDispatcher() : callbacks(std::vector<GamepadCallback>()) {}

  IGamepadDispatcher& GamepadDispatcher::registerCallback(GamepadCallback callback) {
    callbacks.push_back(callback);
    return *this;
  }

  IGamepadDispatcher& GamepadDispatcher::unregisterCallback(GamepadCallback callback) {
    auto end =
        std::remove_if(callbacks.begin(), callbacks.end(), [callback](auto& current) -> bool {
          return callback.target<GamepadCallback>() == current.target<GamepadCallback>();
        });
    callbacks = std::vector<GamepadCallback>(callbacks.begin(), end);
    return *this;
  }

  void GamepadDispatcher::update(Gamepad input) {
    for (auto callback : callbacks) {
      callback(input);
    }
  }
}  // namespace gamepad
