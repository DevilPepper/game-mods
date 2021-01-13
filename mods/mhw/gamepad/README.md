# MHW Gamepad Hook

## What is this?

This plugin simply hooks to what I call `PollController(...)`, a function that's called every frame to update the controller state.
After `PollController(...)` does whatever it needs to do, this plugin will call any functions that subscribed to receive input.
I think this is much cleaner than having multiple plugins hook to `PollController(...)`, although the end result would be just about the same.

This plugin is required for plugins that use [GamepadLib](https://github.com/Stuff-Mods/GamepadLib), i.e. my implementation of HUDToggler, TheFlash and more to come.
_GamepadLib.dll_ must be at the root of the game folder.
