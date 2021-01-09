#include <functional>
#include <vector>
#include "GamepadDispatcher.h"

namespace gamepad {
    GamepadDispatcher::GamepadDispatcher(): callbacks(std::vector<std::function<void(const Gamepad&, const bool(&)[32])>>()) {}

    IGamepadDispatcher& GamepadDispatcher::registerCallback(std::function<void(const Gamepad&, const bool(&)[32])> callback) {
        callbacks.push_back(callback);
        return *this;
    }
    GamepadInput GamepadDispatcher::update(const Gamepad& input) {
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
