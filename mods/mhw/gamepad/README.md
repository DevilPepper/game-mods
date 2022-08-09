# MHW Gamepad Hook

## What is this?

This plugin simply hooks to what I call `PollController(...)`, a function that's called every frame to update the controller state.
After `PollController(...)` does whatever it needs to do, this plugin will call any functions that subscribed to receive input.
I think this is much cleaner than having multiple plugins hook to `PollController(...)`, although the end result would be just about the same.

This plugin is required for plugins that use [GamepadLib](https://github.com/Stuff-Mods/GamepadLib), i.e. my implementation of HUDToggler, TheFlash and more to come.
_GamepadLib.dll_ must be at the root of the game folder.
You should be fine if you unzip the release into that folder.

## Requirements

[Stracker's Loader](https://www.nexusmods.com/monsterhunterworld/mods/1982)

## Compiling and coding

### Prerequisites

- [CMake >= 3.19](https://cmake.org/download/)
- Microsoft Visual C++ (MSVC) compiler toolset
  - This can be installed with Visual Studio installer :vomiting_face:
  - OR by installing [Build Tools for Visual Studio](https://visualstudio.microsoft.com/downloads/#other) separately :muscle:

### Build

Generating project files and building is easy.

```bash
cmake -S . -B build/ -A x64
```

You can find the solution in _build/_ if you want to open it with Visual Studio.

If you want to compile from the cli:

```bash
cmake --build build/ --config <Configuration>
```

> `--config` is optional if you just want Debug

### Symlink

I symlink the built dll to my _nativePC/plugins/_ so that I can do less copying as I make changes. Open a cmd as admin and run this:

```cmd
mklink "C:\Program Files (x86)\Steam\steamapps\common\Monster Hunter World\nativePC\plugins\GamepadHook.dll" "%cd%\build\src\Debug\GamepadHook.dll"

```
