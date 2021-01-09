#include <functional>
#include <vector>
#include "GamepadListener.h"
#include "GamepadEventListeners.h"
#include "gamepad/gamepad.h"
#pragma comment (lib, "stuff.lib")

namespace stuff {
	namespace gamepad {
        GamepadEventListeners::GamepadEventListeners(): callbacks(std::vector<std::function<void(const Gamepad&, const bool(&)[32])>>()) {}

        IGamepadEventListeners& GamepadEventListeners::registerCallback(std::function<void(const Gamepad&, const bool(&)[32])> callback) {
            callbacks.push_back(callback);
            return *this;
        }
        GamepadInput GamepadEventListeners::update(const Gamepad& input) {
            bool stateChanged[32] = { 0 };
            auto changes = input.buttons ^ previous;
            previous = input.buttons;
            for(int i=0; i<32; i++) {
                stateChanged[i] = ((changes & (1<<i)) > 0);
            }
            for (auto callback : callbacks) {
                callback(input, stateChanged);
            }
            return changes;
        }
	}
}
