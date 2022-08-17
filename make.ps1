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
    clean       delete build output and crud that that piles up in the workspace
    purge       run clean first and then delete dependencies
    all         format, build, and test
    external    subcommands to build projects in submodules
    help, -?    show this help message
#>
param(
  [Parameter(Position=0)]
  [ValidateSet("deps", "build", "test", "format", "lint", "clean", "purge", "all", "external", "help")]
  [string]$Command,

  [Parameter(Position=1, ValueFromRemainingArguments=$true)]
  $Rest
)

function Command-Help { Get-Help $PSCommandPath }

function Command-Deps {
  dotnet restore
  cmake -E env CXXFLAGS="/MP" cmake -S . -B build/ -A x64
}

function Command-Build {
  dotnet build --no-restore
  cmake --build build/
}

function Command-Test {
  Command-Build
  dotnet test
  ctest --test-dir build/ --parallel 8 --progress
}

function Command-Format {
  # clang-format -i --style=file $$(find . \( -type f -name "*.cc" -o -name "*.cpp" -o -name "*.h" \) -not -path "./build/*")
  # cmake-format -i $$(find . -name "CMakeLists.txt" -not -path "./build/*")
}

function Command-Lint {
  # clang-tidy?
}

function Command-Clean {
  Get-ChildItem mods,lib -Recurse -Filter bin | foreach { Remove-Item -Recurse -Force $_.FullName }
  Remove-Item -Recurse -Force build/
}

function Command-Purge {
  Command-Clean
  Get-ChildItem mods,lib -Recurse -Filter obj | foreach { Remove-Item -Recurse -Force $_.FullName }
}

function Command-All {
  Command-Format
  Command-Test
}

function Command-External {
  ./external.ps1 $Rest
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
      "clean"     { Command-Clean }
      "purge"     { Command-Purge }
      "all"       { Command-All }
      "external"  { Command-External }
      "help"      { Command-Help }
  }
}
