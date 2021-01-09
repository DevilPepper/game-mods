#pragma once

#include <functional>
#include <vector>
#include "GamepadStruct.h"
#include "IGamepadDispatcher.h"

namespace gamepad {
    class GamepadDispatcher : public IGamepadDispatcher {
        private:
            std::vector<std::function<void(const Gamepad&, const bool(&)[32])>> callbacks;
            GamepadInput previous = 0;
        public:
            GamepadDispatcher();
            IGamepadDispatcher& registerCallback(std::function<void(const Gamepad&, const bool(&)[32])> callback);
            GamepadInput update(const Gamepad& input);
    };
}
