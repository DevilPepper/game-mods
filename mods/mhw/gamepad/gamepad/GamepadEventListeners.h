#pragma once

#ifdef GAMEPAD_LISTENER_IMP
#define GPL_DLL __declspec(dllexport)
#else
#define GPL_DLL __declspec(dllimport)
#endif

#include <functional>
#include "gamepad/Gamepad.h"

namespace stuff {
	namespace gamepad {
        class IGamepadEventListeners {
            public:
                virtual IGamepadEventListeners& registerCallback(std::function<void(const Gamepad&, const bool(&)[32])> callback) = 0;
        };

        GPL_DLL IGamepadEventListeners& GetListener();
	}
}
