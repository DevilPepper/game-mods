#include "GamepadDispatcher.h"

namespace gamepad {
  GamepadDispatcher::GamepadDispatcher() : callbacks(std::list<GamepadCallback>()) {}

  GamepadToken GamepadDispatcher::registerCallback(GamepadCallback callback) {
    callbacks.push_front(callback);
    return callbacks.begin();
  }

  IGamepadDispatcher& GamepadDispatcher::unregisterCallback(GamepadToken token) {
    callbacks.erase(token);
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
