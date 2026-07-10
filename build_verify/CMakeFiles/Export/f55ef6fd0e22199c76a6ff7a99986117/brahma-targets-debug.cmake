#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "brahma::gotcha" for configuration "Debug"
set_property(TARGET brahma::gotcha APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(brahma::gotcha PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib64/libgotcha.so.2.4.4"
  IMPORTED_SONAME_DEBUG "libgotcha.so.2"
  )

list(APPEND _cmake_import_check_targets brahma::gotcha )
list(APPEND _cmake_import_check_files_for_brahma::gotcha "${_IMPORT_PREFIX}/lib64/libgotcha.so.2.4.4" )

# Import target "brahma::brahma" for configuration "Debug"
set_property(TARGET brahma::brahma APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(brahma::brahma PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib64/libbrahma.so.4.1.2"
  IMPORTED_SONAME_DEBUG "libbrahma.so.1"
  )

list(APPEND _cmake_import_check_targets brahma::brahma )
list(APPEND _cmake_import_check_files_for_brahma::brahma "${_IMPORT_PREFIX}/lib64/libbrahma.so.4.1.2" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
