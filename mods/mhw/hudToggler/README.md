# HUDToggler

## What is this?

It's an HUD Toggler. I've seen a few that exist, so it's not a new thing.
This one is a Stracker plugin, so it has direct access to memory
and it's subscribed to receive input every frame.

> TODO: Get this tf outta here

There's also a subtitles toggle that I've been meaning to make it's own plugin.
It lets you toggle subtitles on and off in the middle of a scene.

## Requirements

- [Stracker's Loader](https://www.nexusmods.com/monsterhunterworld/mods/1982)
- [Gamepad Hook](https://github.com/Stuff-Mods/MHW-GamepadHook/releases/latest)

## Game Settings

I recommend going to **Game Settings->HUD Display** and setting everything to off.

## Limitations

- Currently only made for gamepads, but feel free to open a PR adding keyboard and mouse support
- Buttons are hard coded as **L1** for HUD and **Select** for subtitles because there's no clean built in way of parsing a string to an enum.
  - If you require different buttons, for now you'll have to rebuild after you edit it here:
  - <https://github.com/SupaStuff/MHW-GamepadPlugins/blob/c96cb990c24c69d122a9f1f7060bf039dc64d2e8/HUDToggler/dllmain.cpp#L25-L26>

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
mklink "C:\Program Files (x86)\Steam\steamapps\common\Monster Hunter World\nativePC\plugins\HUDToggler.dll" "%cd%\build\src\Debug\HUDToggler.dll"
mklink "C:\Program Files (x86)\Steam\steamapps\common\Monster Hunter World\nativePC\plugins\config\HUD_toggles.json" "%cd%\HUD_toggles.json"

```

> TODO: Give credit to whoever I copied offsets from
