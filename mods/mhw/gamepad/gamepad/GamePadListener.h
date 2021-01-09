#pragma once

#include <functional>
#include <vector>
#include "GamepadEventListeners.h"
#include "gamepad/gamepad.h"
#pragma comment (lib, "stuff.lib")

namespace stuff {
	namespace gamepad {
        class GamepadEventListeners : public IGamepadEventListeners {
            private:
                std::vector<std::function<void(const Gamepad&, const bool(&)[32])>> callbacks;
                GamepadInput previous = 0;
            public:
                GamepadEventListeners();
                IGamepadEventListeners& registerCallback(std::function<void(const Gamepad&, const bool(&)[32])> callback);
                GamepadInput update(const Gamepad& input);
        };
	}
}
