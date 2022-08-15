SHELL := bash
.ONESHELL:
.SHELLFLAGS := -eu -o pipefail -c
.DELETE_ON_ERROR:
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules
.RECIPEPREFIX = >

default: build
.PHONY: all build clean format help lint purge test

# help:
# > @echo "Usage:"
# > @echo -e "\tmake <target(s)>\n"
# > @echo "Targets:"
# > @tabs 24
# > @sed -n '/^# @help:/{N;p;}' Makefile | sed 's/^#.*: //g' | sed 's/:.*$$//g' | tac | paste -s -d"\t\n" | sed 's/^/    /g' | tac
# > @tabs 4

# @help: Install node dependencies and generate VS project files
deps:
> @dotnet restore
# Why not only in build??
> @cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build/ -A x64

# @help: Default target (just run `make`). Incremental builds for dev
build:
> @dotnet build --no-restore
> @cmake --build build/ --config Debug

# @help: Run all tests
test: build
> @dotnet test
> @ctest --test-dir build/ --parallel 8 --progress

# @help: Lint and format all files
# format:
# > @clang-format -i --style=file $$(find . \( -type f -name "*.cc" -o -name "*.cpp" -o -name "*.h" \) -not -path "./build/*")
# > @cmake-format -i $$(find . -name "CMakeLists.txt" -not -path "./build/*")

# @help: Lint all files and report violations
# lint:
# TODO: use clang-tidy here

# @help: Delete build output and crud that that piles up in the workspace
clean:
> @Get-ChildItem mods,lib -Recurse -Filter bin | foreach { Remove-Item -Recurse -Force $_.FullName }
> @Remove-Item -Recurse -Force build/

# @help: Run clean first and then delete dependencies and lockfile(s)
purge: clean
> @Get-ChildItem mods,lib -Recurse -Filter obj | foreach { Remove-Item -Recurse -Force $_.FullName }

# @help: format build and test
all: format test
