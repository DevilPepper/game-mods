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
                std::vector<std::function<void(Gamepad&, bool[32])>> callbacks;
            public:
                GamepadEventListeners();
                IGamepadEventListeners& registerCallback(std::function<void(Gamepad&, bool[32])> callback);
                void update(Gamepad input);
        };
	}
}
