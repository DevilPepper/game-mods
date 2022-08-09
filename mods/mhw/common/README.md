# MHW Common Lib

## What is this?

This is a library abstracting away some logic you need to write over and over again to make a Stracker's plugin.
Hopefully, it helps write cleaner plugins.

## Dependencies

- [Stuff Lib](https://github.com/Stuff-Mods/StuffLib) (stuff externs are defined in mhw-common)
- My [fork](https://github.com/ForksKnivesAndSpoons/MHW-QuestLoader) of [Stracker's Loader](https://github.com/Strackeror/MHW-QuestLoader).

## Docs?

Maybe I'll use Doxygen to generate them.

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
