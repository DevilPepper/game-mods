project(stuff)
FILE(GLOB_RECURSE stuffSources CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR} *.h *.cpp)
add_library(stuff STATIC ${stuffSources})
target_include_directories(stuff PUBLIC .)
target_compile_features(stuff PRIVATE cxx_std_17)
target_link_libraries(stuff
                      PUBLIC nlohmann_json::nlohmann_json
                      PRIVATE minhook::minhook
)
