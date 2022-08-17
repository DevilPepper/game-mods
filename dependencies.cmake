include(FetchContent)

set(YAML_BUILD_SHARED_LIBS ON CACHE BOOL "build dll and define external symbols")
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "don't build unwanted tools")
# 0.7.0
# set(YAML_CPP_FORMAT_SOURCE OFF CACHE BOOL "why would I want to format code from a library?!")
# 0.6.3
set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "why would I want to build tests for a library?!")
set(YAML_CPP_INSTALL OFF CACHE BOOL "don't generate install targets")

FetchContent_Declare(
  minhook
  GIT_REPOSITORY "https://github.com/TsudaKageyu/minhook"
  GIT_TAG "4a455528f61b5a375b1f9d44e7d296d47f18bb18"
)
FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY "https://github.com/jbeder/yaml-cpp.git"
  GIT_TAG "9a3624205e8774953ef18f57067b3426c1c5ada6"
)

FetchContent_MakeAvailable(minhook)
FetchContent_MakeAvailable(yaml-cpp)
