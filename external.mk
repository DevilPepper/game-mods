SHELL := bash
.ONESHELL:
.SHELLFLAGS := -eu -o pipefail -c
.DELETE_ON_ERROR:
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules
.RECIPEPREFIX = >

default: help
.PHONY: all help hunterpie

# @help: Build HunterPie using MSbuild since HunterPie.Native is not supported by dotnet cli
hunterpie:
> @$$MSVS = "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools"
> @Import-Module $$MSVS\Common7\Tools\Microsoft.VisualStudio.DevShell.dll
> @Enter-VsDevShell -SkipAutomaticLocation -SetDefaultWindowTitle -InstallPath $$MSVS
> @msbuild .\mods\mhw\hunterpie\HunterPie.sln -m /t:Restore
> @msbuild .\mods\mhw\hunterpie\HunterPie.sln -m /p:Configuration=Debug
