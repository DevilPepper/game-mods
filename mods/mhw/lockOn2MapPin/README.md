# LockOn2MapPin

## What is this?

When you lock on to a monster (R3), your trailraider will not automatically track the monster.
This is because the map pin doesn't get placed on the map for you when you lock on.
This plugin will do that for you. Cycling lock on targets will now also cycle large monster map pins.

## Requirements

[Stracker's Loader](https://www.nexusmods.com/monsterhunterworld/mods/1982)

## Game Settings

- **Camera -> Target Settings**: "Large Monsters Only" (Required)
- **Camera -> Camera Style**: "Do Not Focus" (Recommended if you also don't like lock on)

It doesn't work correctly if "All Monsters" is selected for **Target Settings**. You gotta live with that.

## Know Limitation

The trailraider doesn't change it's target mid-ride,
so you have to get off and on again for it to pick up the change.
I might fix this eventually if possible, but it's not that important.
It's still better than opening the map to set a pin.

## Compiling and coding

### Prerequisites

- [CMake >= 3.19](https://cmake.org/download/)
- Microsoft Visual C++ (MSVC) compiler toolset
  - This can be installed with Visual Studio installer :vomiting_face:
  - OR by installing [Build Tools for Visual Studio](https://visualstudio.microsoft.com/downloads/#other) separately :muscle:
- [vcpkg](https://github.com/microsoft/vcpkg)

### vcpkg

I cloned it to _C:\\dev\\vcpkg_, but this can be anywhere.
Follow the instructions in their readme's [Getting Started](https://github.com/microsoft/vcpkg#getting-started).

In my powershell profile, I have this:

```pwsh
# vcpkg
$env:Path+=";C:\dev\vcpkg"
$env:VCPKG_DEFAULT_TRIPLET="x64-windows"
$env:VCPKG_FEATURE_FLAGS="manifests,versions"
$env:VCPKG_DISABLE_METRICS=$True
$env:VCPKG_ROOT="C:/dev/vcpkg"
```

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
mklink "C:\Program Files (x86)\Steam\steamapps\common\Monster Hunter World\nativePC\plugins\LockOn2MapPin.dll" "%cd%\build\src\Debug\LockOn2MapPin.dll"

```
