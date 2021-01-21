include(FetchContent)
include(cmake/add_FetchContent_MakeAvailableNotAll.cmake)

FetchContent_Declare(
        minhook
        GIT_REPOSITORY "https://github.com/TsudaKageyu/minhook"
        GIT_TAG "3f2e34976c1685ee372a09f54c0c8c8f4240ef90"
)
FetchContent_Declare(
        GamepadLib
        GIT_REPOSITORY "https://github.com/Stuff-Mods/GamepadLib"
        GIT_TAG "6f16e7fea327fe2e21f171ac7b552ab24ee69384"
)
FetchContent_Declare(
        stuff
        GIT_REPOSITORY "https://github.com/Stuff-Mods/StuffLib"
        GIT_TAG "2ac3bfda4c075fc8a6bdc25a94bf7d750c6f95de"
)
FetchContent_Declare(
        mhw-common
        GIT_REPOSITORY "https://github.com/Stuff-Mods/MHW-CommonLib"
        GIT_TAG "7f611e344cfa2b97e774c56605546a4a2b8b9e6c"
)

FetchContent_MakeAvailableNotAll(minhook)
FetchContent_MakeAvailable(GamepadLib)
FetchContent_MakeAvailable(stuff)
FetchContent_MakeAvailable(mhw-common)
