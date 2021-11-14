#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Trantor::Trantor" for configuration "Release"
set_property(TARGET Trantor::Trantor APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Trantor::Trantor PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/trantor.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Trantor::Trantor )
list(APPEND _IMPORT_CHECK_FILES_FOR_Trantor::Trantor "${_IMPORT_PREFIX}/lib/trantor.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
