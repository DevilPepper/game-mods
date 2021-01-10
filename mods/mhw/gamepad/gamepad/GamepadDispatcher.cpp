#include "GamepadDispatcher.h"

#include <functional>
#include <vector>

namespace gamepad {
  GamepadDispatcher::GamepadDispatcher() :
      callbacks(std::vector<std::function<void(const Gamepad&)>>()) {}

  IGamepadDispatcher& GamepadDispatcher::registerCallback(
      std::function<void(const Gamepad&)> callback) {
    callbacks.push_back(callback);
    return *this;
  }
  void GamepadDispatcher::update(Gamepad input) {
    for (auto callback : callbacks) {
      callback(input);
    }
  }
}  // namespace gamepad
