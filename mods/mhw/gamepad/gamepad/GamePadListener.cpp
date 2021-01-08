#include <functional>
#include <vector>
#include "GamepadListener.h"
#include "GamepadEventListeners.h"
#include "gamepad/gamepad.h"
#pragma comment (lib, "stuff.lib")

namespace stuff {
	namespace gamepad {
        GamepadEventListeners::GamepadEventListeners(): callbacks(std::vector<std::function<void(Gamepad&, bool[32])>>()) {}

        IGamepadEventListeners& GamepadEventListeners::registerCallback(std::function<void(Gamepad&, bool[32])> callback) {
            callbacks.push_back(callback);
            return *this;
        }
        void GamepadEventListeners::update(Gamepad input) {
            for (auto callback : callbacks) {
                callback(input, nullptr);
            }
        }
	}
}
