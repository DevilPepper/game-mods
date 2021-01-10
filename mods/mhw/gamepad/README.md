# Gamepad Hook

## What is this?

It's both a plugin and a library allowing other plugins to subscribe to receive gamepad input.

### Plugin

This plugin simply hooks to what I call `PollController(...)`, a function that's called every frame to update the controller state.
After `PollController(...)` does whatever it needs to do, this plugin will call any functions that subscribed to receive input.
I think this is much cleaner than having multiple plugins hook to `PollController(...)`, although the end result would be just about the same.

This plugin is required for plugins that use it's library, i.e. my implementation of HUDToggler, and more to come.
Unfortunately, at this time, _GamepadHook.dll_ needs to be both at the root of the game folder as well as in _nativePC/plugins/_. :(

### Library

To use the library, I recommend using CMake's `FetchContent`:

```CMake
include(FetchContent)

FetchContent_Declare(GamepadHook
  GIT_REPOSITORY https://github.com/SupaStuff/MHW-GamepadPlugins.git
  GIT_TAG 710f81b26ffbc8272a1a71cf2229b8eec2535dca)

FetchContent_GetProperties(GamepadHook)
if(NOT GamepadHook_POPULATED)
  FetchContent_Populate(GamepadHook)
  add_subdirectory(${GamepadHook_SOURCE_DIR} ${GamepadHook_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

target_link_libraries(MyDopeAFPlugin PRIVATE GamepadHook)
```

Alternatively, you could probably grab the headers and the lib file and dump it into your project.
I haven't tried it and I think the effort and cognitive overhead isn't really worth trying.
But you probably know what you're doing if you prefer this method.

## API

Add this to your includes:

```cpp
#include "gamepad.h"
#pragma comment(lib, "GamepadHook.lib")
```

_gamepad.h_ includes all of these that you may include individually if you prefer:

- [Button.h](https://github.com/SupaStuff/MHW-GamepadPlugins/blob/master/GamepadHook/GamepadHeaders/Button.h): Defines an enum for button names (Currently only PS4 controller buttons, but matching buttons should work)
- [Buttons.h](https://github.com/SupaStuff/MHW-GamepadPlugins/blob/master/GamepadHook/GamepadHeaders/Buttons.h): Defines a list of `GamepadInput` representing 1 button each. These can be combined by using bitwise OR. i.e.:

```cpp
auto btns = Buttons[Button::Circle] | Buttons[Button::Triangle]
```

- [GamepadInput.h](https://github.com/SupaStuff/MHW-GamepadPlugins/blob/master/GamepadHook/GamepadHeaders/GamepadInput.h): Just a typedef for GamepadInput. It's an unsigned 32 bit integer. Each bit represents a button
- [GamepadInputHelper.h](https://github.com/SupaStuff/MHW-GamepadPlugins/blob/master/GamepadHook/GamepadHeaders/GamepadInputHelper.h): A couple of helper functions
- [GamepadStruct.h](https://github.com/SupaStuff/MHW-GamepadPlugins/blob/master/GamepadHook/GamepadHeaders/GamepadStruct.h): The Gamepad struct that's taken from memory every frame and callbacks accept as input
- [IGamepadDispatcher.h](https://github.com/SupaStuff/MHW-GamepadPlugins/blob/master/GamepadHook/GamepadHeaders/IGamepadDispatcher.h): The dispatcher interface and `gamepad::GetDispatcher()` are here

### Subscribing

The Dispatcher will call all functions subscribed to recieve input every frame. You need to define a `void` function with a `const Gamepad&` parameter:

```cpp
void callback(const Gamepad& gamepad) { 
  // Do w/e with `gamepad` this frame (readonly)
}
```

This can also be an [std::function](https://en.cppreference.com/w/cpp/utility/functional/function), i.e. a lambda, a curried function, a Callable...

Then you get the dispatcher from the dll and subscribe using your callback:

```cpp
  gamepad::GetDispatcher().registerCallback(&callback);
```

You can chain registering...

```cpp
  gamepad::GetDispatcher()
    .registerCallback(&callback0)
    .registerCallback(&callback1)
    .registerCallback(&callback2);
```

### Gamepad

The `Gamepad` struct should be self explanatory, but I think I should give some explanation for the fields.

`Gamepad.buttons`: This has the currently pressed buttons. Useful for doing something continuously while a button is held:

```cpp
(gamepad.buttons & btns) > 0
```

A helper function exists that does this for you. Look in [GamepadInputHelper.h](https://github.com/SupaStuff/MHW-GamepadPlugins/blob/master/GamepadHook/GamepadHeaders/GamepadInputHelper.h)

`Gamepad.buttonsJust{Pressed|Released}`: Similarly to buttons, these represent buttons that were just pressed/released this frame. Useful for doing something just once on press/release. Helpers exist for these.

`Gamepad.simultaneousButtons_NotFullyUnderstood_DoNotUse`: Doesn't behave consistently. Sometimes it will alternate between held buttons if they weren't pressed at the same time. But it's not a good indicator of anything.

`Gamepad.{left|right}Stick{X|Y}`: Ranges from -1.00 to +1.00, representing how much the sticks are tilted. Left and Down are negative. Sometimes they go past these bounds, though... Rotate from far X to far Y and you'll see.

`Gamepad.{left|right}StickMagnitude`: &Sqrt;(X<sup>2</sup> +Y<sup>2</sup>)

`Gamepad.{left|right}TriggerMagnitude`: Ranges from 0.00 to +1.00, representing how much the trigger is pressed down.

`Gamepad.pressDuration`: An array who's elements represent the time in seconds that a button has been held. The elements can be accessed with the enum `Button`:

```cpp
auto GS_Charge = Gamepad.pressDuration[Button::Triangle];
```
