#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Drogon::Drogon" for configuration "Release"
set_property(TARGET Drogon::Drogon APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Drogon::Drogon PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/drogon.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/drogon.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS Drogon::Drogon )
list(APPEND _IMPORT_CHECK_FILES_FOR_Drogon::Drogon "${_IMPORT_PREFIX}/lib/drogon.lib" "${_IMPORT_PREFIX}/bin/drogon.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
