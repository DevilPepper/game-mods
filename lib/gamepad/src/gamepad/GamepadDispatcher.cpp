#include "GamepadDispatcher.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

namespace gamepad {
  GamepadDispatcher::GamepadDispatcher() : callbacks(std::list<GamepadCallback>()) {}

  GamepadToken GamepadDispatcher::registerCallback(GamepadCallback callback) {
    callbacks.push_front(callback);
    std::cout << "Registered callback. # registered: " << callbacks.size() << std::endl;
    return callbacks.begin();
  }

  IGamepadDispatcher& GamepadDispatcher::unregisterCallback(GamepadToken token) {
    callbacks.erase(token);
    std::cout << "Unregistered callback. # registered: " << callbacks.size() << std::endl;
    return *this;
  }

  IGamepadDispatcher& GamepadDispatcher::registerCallback(GamepadCallback callback,
                                                          GamepadTokens& tokens) {
    tokens.push(registerCallback(callback));
    return *this;
  }
  void GamepadDispatcher::unregisterCallback(GamepadTokens& tokens) {
    while (!tokens.empty()) {
      unregisterCallback(tokens.front());
      tokens.pop();
    }
  }

  void GamepadDispatcher::update(Gamepad input) {
    for (auto callback : callbacks) {
      callback(input);
    }
  }
}  // namespace gamepad
