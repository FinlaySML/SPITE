#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "soloud" for configuration "RelWithDebInfo"
set_property(TARGET soloud APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(soloud PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "C;CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELWITHDEBINFO "C:/Users/2100719/source/repos/FinlaySML/SPITE/lib/x64/SDL2.lib"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/soloud.lib"
  )

list(APPEND _cmake_import_check_targets soloud )
list(APPEND _cmake_import_check_files_for_soloud "${_IMPORT_PREFIX}/lib/soloud.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
