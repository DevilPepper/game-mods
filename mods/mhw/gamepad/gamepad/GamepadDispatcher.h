#pragma once

#include <functional>
#include <vector>
#include "GamepadStruct.h"
#include "IGamepadDispatcher.h"

namespace gamepad {
    class GamepadDispatcher : public IGamepadDispatcher {
        private:
            std::vector<std::function<void(const Gamepad&)>> callbacks;
        public:
            GamepadDispatcher();
            IGamepadDispatcher& registerCallback(std::function<void(const Gamepad&)> callback);
            void update(Gamepad input);
    };
}
