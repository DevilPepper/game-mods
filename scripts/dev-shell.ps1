$MSVS = vswhere.exe -prerelease -latest -property installationPath
Import-Module $MSVS\Common7\Tools\Microsoft.VisualStudio.DevShell.dll
Enter-VsDevShell -SkipAutomaticLocation -DevCmdArguments '-arch=x64 -no_logo' -InstallPath $MSVS
