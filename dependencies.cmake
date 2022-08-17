include(FetchContent)

set(YAML_BUILD_SHARED_LIBS ON CACHE BOOL "build dll and define external symbols")
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "don't build unwanted tools" FORCE)
set(YAML_CPP_FORMAT_SOURCE OFF CACHE BOOL "why would I want to format code from a library?!" FORCE)

FetchContent_Declare(
  minhook
  GIT_REPOSITORY "https://github.com/TsudaKageyu/minhook"
  GIT_TAG "4a455528f61b5a375b1f9d44e7d296d47f18bb18"
)
FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY "https://github.com/jbeder/yaml-cpp.git"
  GIT_TAG "c73ee34704c512ebe915b283645aefa9f424a22f"
)

FetchContent_MakeAvailable(minhook)
FetchContent_MakeAvailable(yaml-cpp)
