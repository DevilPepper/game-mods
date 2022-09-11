FetchContent_Declare(
  memorymodule
  GIT_REPOSITORY "https://github.com/fancycode/MemoryModule"
  GIT_TAG "5f83e41c3a3e7c6e8284a5c1afa5a38790809461"
)
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

MakeAvailable(memorymodule)
MakeAvailable(minhook)
MakeAvailable(yaml-cpp)
