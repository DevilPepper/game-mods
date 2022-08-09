#pragma once

#ifdef GAMEPAD_LISTENER_IMP
#define GPL_DLL __declspec(dllexport)
#else
#define GPL_DLL __declspec(dllimport)
#endif

#include <functional>
#include <list>
#include <queue>

#include "GamepadStruct.h"

namespace gamepad {
  using GamepadCallback = std::function<void(const Gamepad&)>;
  using GamepadToken = std::list<GamepadCallback>::iterator;
  using GamepadTokens = std::queue<GamepadToken>;

  class IGamepadDispatcher {
   public:
    virtual GamepadToken registerCallback(GamepadCallback callback) = 0;
    virtual IGamepadDispatcher& unregisterCallback(GamepadToken token) = 0;

    virtual IGamepadDispatcher& registerCallback(GamepadCallback callback,
                                                 GamepadTokens& tokens) = 0;
    virtual void unregisterCallback(GamepadTokens& tokens) = 0;

    virtual void update(Gamepad input) = 0;
  };

  GPL_DLL IGamepadDispatcher& GetDispatcher();
}  // namespace gamepad
