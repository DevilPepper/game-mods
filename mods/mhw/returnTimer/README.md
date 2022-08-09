# Return Timer

## What is this?

This plugin lets you control the quest end timer:

| Input                      | Effect                       |
| :------------------------- | :--------------------------- |
| Hold L1 and press Triangle | Adds 10 seconds to the timer |
| Hold L1 and press Circle   | Toggles freeze timer on/off  |
| Hold L1 and press X        | Ends the timer               |

## Requirements

- [Stracker's Loader](https://www.nexusmods.com/monsterhunterworld/mods/1982)
- [Gamepad Hook](https://github.com/Stuff-Mods/MHW-GamepadHook/releases/latest)

## Limitations

It's made only for gamepads at this time, but it's easy to add other command sources (i.e. chat commands, keyboard, mouse,...):

```cpp
void ReturnTimer::controlTimerSomeOtherWay(...) {
  auto [timerAddr, isEndOfQuest] = readTimer();
  if (isEndOfQuest) {
    if (freezeTime) {
      freezeTimer(timerAddr);
    }
    ...
    if (shouldAddTime) {
      // Doesn't have to be 10 (imagine typing `/timer +20`)
      addSeconds(10, timerAddr);
    } else if (shouldTogleFreezeTimer) {
      toggleFreezeTimer(timerAddr);
    } else if (shouldEndTimer) {
      endTimer(timerAddr);
    }
  }
}
```

Maybe I'll add more command sources some day. Or feel free to open a PR.

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
mklink "C:\Program Files (x86)\Steam\steamapps\common\Monster Hunter World\nativePC\plugins\ReturnTimer.dll" "%cd%\build\src\Debug\ReturnTimer.dll"

```

## Credits

- **Marcus101RR** for his [cheat table](https://www.nexusmods.com/monsterhunterworld/mods/2161)
  - And anyone that contributed to the pointers section
