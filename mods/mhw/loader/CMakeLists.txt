project(loader)
FILE(GLOB_RECURSE loaderSources CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src *.h *.cpp)
add_library(loader SHARED ${loaderSources})
target_compile_definitions(loader PRIVATE DINPUT8MHW_EXPORTS)
target_compile_features(loader PRIVATE cxx_std_20)
target_link_libraries(loader
  PRIVATE
    MemoryModule
    yaml-cpp
)
