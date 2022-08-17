project(TheFlash)
FILE(GLOB_RECURSE TheFlashSources CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src *.h *.cpp)
add_library(TheFlash MODULE ${TheFlashSources})
target_compile_features(TheFlash PRIVATE cxx_std_20)
target_link_libraries(TheFlash
  PRIVATE
    stuff
    mhw-common
    GamepadLib
    yaml-cpp
)
