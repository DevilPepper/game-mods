#pragma once

namespace stuff {
	namespace gamepad {
        enum BTN_ACTION { PRESSED, RELEASED, LONG_PRESS, LONG_RELEASE };
        class GamepadEventListeners
        {
            // Needs to keep track of time button is held/released
        public:
            static GamepadEventListeners& getInstance()
            {
                static GamepadEventListeners instance;
                return instance;
            }
        private:
            GamepadEventListeners() {}
        public:
            GamepadEventListeners(GamepadEventListeners const&) = delete;
            void operator=(GamepadEventListeners const&) = delete;
            // parameters are callback, button(s) to handle
            void registerButtonPressedHandler();
            void registerButtonReleasedHandler();
            // and optional start and end times
            void registerButtonLongPressedHandler();
            void registerButtonHeldHandler();
        };
	}
}