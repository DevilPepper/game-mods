#pragma once

#ifdef GAMEPAD_LISTENER_IMP
#define GPL_DLL __declspec(dllexport)
#else
#define GPL_DLL __declspec(dllimport)
#endif

#include <functional>
#include "GamepadStruct.h"

namespace gamepad {
        class IGamepadDispatcher {
                public:
                virtual IGamepadDispatcher& registerCallback(std::function<void(const Gamepad&)> callback) = 0;
        };

        GPL_DLL IGamepadDispatcher& GetDispatcher();
}
