project(mhw)

add_subdirectory(loader)
add_subdirectory(common)
add_subdirectory(gamepad)
add_subdirectory(hudToggler)
add_subdirectory(lockOn2MapPin)
add_subdirectory(returnTimer)
add_subdirectory(theFlash)
add_subdirectory(toggleSubtitles)

if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/poc")
  add_subdirectory(poc)
endif()
