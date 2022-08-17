<#
.SYNOPSIS
Build projects in submodules

.DESCRIPTION
USAGE
    make external <command>

COMMANDS
    hunterpie   build HunterPie using MSbuild since HunterPie.Native is not supported by dotnet cli
    all         default command (just run `make external`). Build all submodule projects
    help, -?    show this help message
#>
param(
  [Parameter(Position=0)]
  [ValidateSet("", "all", "help", "hunterpie")]
  [string]$Command
)

function Command-Help() { Get-Help $PSCommandPath }

function Command-HunterPie() {
  msbuild lib/hunterpie/HunterPie.sln -m /t:Restore
  msbuild lib/hunterpie/HunterPie.sln -m /p:Configuration=Debug
}

function Command-All() {
  Command-HunterPie
}

if (!$Command) {
    Command-All
} else {
  switch ($Command) {
      "hunterpie"  { Command-HunterPie }
      "all"        { Command-All }
      "help"       { Command-Help }
  }
}
