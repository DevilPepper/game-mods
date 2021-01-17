# The Flash

## What is this?

This plugin lets you zip around town like The Flash by pressing L2.
The speed is increased as you press down further.

## Requirements

- [Stracker's Loader](https://www.nexusmods.com/monsterhunterworld/mods/1982)
- [Gamepad Hook](https://github.com/Stuff-Mods/MHW-GamepadHook/releases/latest)

## Limitations

The following movements are not multiplied because I don't know what floats to poke:

- Walk (small tilt - in quest)
- Run (full tilt - in quest)
- Run for your life
- Crouch walk
- Sneak walk
- Roll
- Climb
- Fast Climb

That's a lot, I know. I started with what was in Marcus's cheat table.
I imagine these won't be hard to find, but feel free to open a PR adding multipliers for these if you find it first.

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
mklink "C:\Program Files (x86)\Steam\steamapps\common\Monster Hunter World\nativePC\plugins\config\TheFlash.json" "%cd%\TheFlash.json"

```

## Credits

- **Marcus101RR** for his [cheat table](https://www.nexusmods.com/monsterhunterworld/mods/2161)
  - And anyone that contributed to the pointers section
- **Haato** because I copied ZoneId from the latest address map included in [HunterPie](https://github.com/Haato3o/HunterPie)
