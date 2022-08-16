include(FetchContent)
include(cmake/add_FetchContent_MakeAvailableNotAll.cmake)
FetchContent_Declare(
        minhook
        GIT_REPOSITORY "https://github.com/TsudaKageyu/minhook"
        GIT_TAG "423d1e45af2ed2719a5c31e990e935ef301ed9c3"
)
FetchContent_MakeAvailableNotAll(minhook)
