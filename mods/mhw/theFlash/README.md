# The Flash

## What is this?

This plugin lets you zip around town like The Flash by pressing R2.
The speed is increased as you press down further.

## Requirements

- [Stracker's Loader](https://www.nexusmods.com/monsterhunterworld/mods/1982)
- [Gamepad Hook](https://github.com/Stuff-Mods/MHW-GamepadHook/releases/latest)

## Limitations

It's made to only work while you are not on the field.
The in quest controls makes it hard to pick a good speed up button,
but also zipping around in quest is not cool.
Build your own plugin if this is what you require.

## Compiling and coding

This project uses CMake and depends on my [fork](https://github.com/ForksKnivesAndSpoons/MHW-QuestLoader) of [Stracker's Loader](https://github.com/Strackeror/MHW-QuestLoader).

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
mklink "C:\Program Files (x86)\Steam\steamapps\common\Monster Hunter World\nativePC\plugins\TheFlash.dll" "%cd%\build\src\Debug\TheFlash.dll"

```

> TODO: Give credit to whoever I copied offsets from
