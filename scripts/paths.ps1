function Copy-Force([string]$source, [string]$destination) {
  if (Test-Path -Path $source) {
    echo "`u{2795} `"${source}`" -> `"${destination}`""
    $directory = $(Split-Path -Path $destination -Parent)
    New-Item -ItemType "directory" -Path $directory -Force > $null
    Copy-Item $source -Destination $destination
  }
}

function Copy-Safe([string]$source, [string]$destination) {
  if (-not (Test-Path -Path $destination)) {
    Copy-Force $source $destination
  }
}

function Symlink([string]$source, [string]$destination) {
  if (Test-Path -Path $source) {
    echo "`u{1f517} `"${source}`" -> `"${destination}`""
    if (Test-Path -Path $destination) {
      Remove-Item -Force $destination
    }
    $directory = $(Split-Path -Path $destination -Parent)
    New-Item -ItemType "directory" -Path $directory -Force > $null
    New-Item -ItemType SymbolicLink -Target $source -Path $destination > $null
  }
}

$MHW = "C:\Program Files (x86)\Steam\steamapps\common\Monster Hunter World"
