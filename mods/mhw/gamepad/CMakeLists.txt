project(GamepadHook)
FILE(GLOB_RECURSE GamepadHookSources CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src *.h *.cpp)
add_library(GamepadHook MODULE ${GamepadHookSources})
target_compile_definitions(GamepadHook PRIVATE GAMEPAD_LISTENER_IMP)
target_compile_features(GamepadHook PRIVATE cxx_std_20)
target_link_libraries(GamepadHook
  PRIVATE
    stuff
    mhw-common
    GamepadLib
    yaml-cpp
)
