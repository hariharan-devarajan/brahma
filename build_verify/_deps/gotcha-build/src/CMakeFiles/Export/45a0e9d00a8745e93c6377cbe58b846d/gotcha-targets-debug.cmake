#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "gotcha" for configuration "Debug"
set_property(TARGET gotcha APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(gotcha PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib64/libgotcha.so.2.4.4"
  IMPORTED_SONAME_DEBUG "libgotcha.so.2"
  )

list(APPEND _cmake_import_check_targets gotcha )
list(APPEND _cmake_import_check_files_for_gotcha "${_IMPORT_PREFIX}/lib64/libgotcha.so.2.4.4" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
