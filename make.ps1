<#
.SYNOPSIS
This script provides some commands that you should find useful for dev.

.DESCRIPTION
USAGE
    make <command>

COMMANDS
    deps        install NuGet dependencies and generate VS project files
    build       default command (just run `make`). Incremental builds for dev
    test        run all tests
    format      format all files
    lint        lint all files and report violations
    setup       copy configs to game directories, etc if they don't already exist.
                Requires admin privileges or developer mode because some are symlinks.
                Symlinks will replace existing files.
    install     copy builds to game directories, etc, overwriting old versions
    clean       delete build output and crud that that piles up in the workspace
    purge       run clean first and then delete dependencies
    all         format, build, and test
    external    subcommands to build projects in submodules
    help, -?    show this help message
#>
param(
  [Parameter(Position=0)]
  [ValidateSet("all", "build", "clean", "deps", "env", "external", "format", "help", "install", "lint", "purge", "setup", "test")]
  [string]$Command,

  [Parameter(Position=1, ValueFromRemainingArguments=$true)]
  $Rest
)

function Command-Help() { Get-Help $PSCommandPath }

function Command-Deps() {
  $BuildConfiguration = $env:BuildConfiguration ?? "Debug"

  dotnet restore
  cmake -DCMAKE_BUILD_TYPE="$($BuildConfiguration)" -S . -B build/ -G Ninja
}

function Command-Build() {
  $BuildConfiguration = $env:BuildConfiguration ?? "Debug"

  dotnet build --no-restore --configuration $BuildConfiguration
  cmake --build build/ --config $BuildConfiguration
}

function Command-Test() {
  $BuildConfiguration = $env:BuildConfiguration ?? "Debug"
  Command-Build

  dotnet test --no-build
  ctest --test-dir build/ --parallel 8 --progress --build-config $BuildConfiguration
}

function Command-Format() {
  # clang-format -i --style=file $$(find . \( -type f -name "*.cc" -o -name "*.cpp" -o -name "*.h" \) -not -path "./build/*")
  # cmake-format -i $$(find . -name "CMakeLists.txt" -not -path "./build/*")
}

function Command-Lint() {
  # clang-tidy?
}

function Command-Setup() {
  ./scripts/setup.ps1
}

function Command-Install() {
  ./scripts/install.ps1 $Rest
}

function Command-Clean() {
  Get-ChildItem mods,lib,external -Recurse -Filter bin | foreach { Remove-Item -Recurse -Force $_.FullName }
  Remove-Item -Recurse -Force build/
}

function Command-Purge() {
  Command-Clean
  Get-ChildItem mods,lib,external -Recurse -Filter obj | foreach { Remove-Item -Recurse -Force $_.FullName }
}

function Command-All() {
  Command-Format
  Command-Test
}

function Command-Env() {
  echo "`$env:BuildConfiguration = $($env:BuildConfiguration ?? 'Debug')"
}

function Command-External() {
  ./scripts/external.ps1 $Rest
}

if (!$Command) {
    Command-Build
} else {
  switch ($Command) {
      "deps"      { Command-Deps }
      "build"     { Command-Build }
      "test"      { Command-Test }
      "format"    { Command-Format }
      "lint"      { Command-Lint }
      "setup"     { Command-Setup }
      "install"   { Command-Install }
      "clean"     { Command-Clean }
      "purge"     { Command-Purge }
      "all"       { Command-All }
      "env"       { Command-Env }
      "external"  { Command-External }
      "help"      { Command-Help }
  }
}
