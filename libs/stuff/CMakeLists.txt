project(stuff)
FILE(GLOB_RECURSE stuffSources CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src *.h *.cpp)
add_library(stuff STATIC ${stuffSources})
target_include_directories(stuff PUBLIC src)
target_compile_features(stuff PRIVATE cxx_std_20)
target_link_libraries(stuff
  PRIVATE
    minhook
)
