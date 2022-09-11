set(YAML_BUILD_SHARED_LIBS ON CACHE BOOL "build dll and define external symbols")
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "don't build unwanted tools")
set(YAML_CPP_FORMAT_SOURCE OFF CACHE BOOL "why would I want to format code from a library?!")
set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "why would I want to build tests for a library?!")
set(YAML_CPP_INSTALL OFF CACHE BOOL "don't generate install targets")

include(FetchContent)
include(MakeAvailable.cmake)
include(dependencies.cmake)
