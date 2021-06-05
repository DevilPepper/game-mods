# StuffLib

## What is this?

This is a library with some wrappers around
[MinHook](https://github.com/TsudaKageyu/minhook),
some functions to follow pointers represented as a vector of offsets,
and some type definitions from Ghidra.

## Docs?

Maybe I'll use Doxygen to generate them.

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
