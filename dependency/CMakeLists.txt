include(brahma-utils)
if (BRAHMA_LOGGER STREQUAL "CPP_LOGGER")
    fetch_package(NAME cpp-logger cpp_logger CPP_LOGGER Cpp_logger
                  VERSION 1.1.2
                  GIT https://github.com/JaeseungYeom/cpp-logger.git
                  TAG cmake_fix
                  #GIT https://github.com/hariharan-devarajan/cpp-logger.git
                  #TAG b18d21b1ce67da49196a195d0cb496bd083cca38
                  #SHALLOW
                  #DIAG
                  VARS "CPP_LOGGER_ENABLE_TESTING OFF BOOL"
                       "CPP_LOGGER_LIBDIR_AS_LIB ${BRAHMA_LIBDIR_AS_LIB} BOOL")

    # Propagate up one more level to top-level CMakeLists.txt
    set(cpp-logger_POPULATED    "${cpp-logger_POPULATED}"    PARENT_SCOPE)
    set(cpp-logger_INCLUDE_DIRS "${cpp-logger_INCLUDE_DIRS}" PARENT_SCOPE)
    set(cpp-logger_LIBRARIES    "${cpp-logger_LIBRARIES}"    PARENT_SCOPE)
    set(cpp-logger_FOUND        "${cpp-logger_FOUND}"        PARENT_SCOPE)
endif()

fetch_package(NAME gotcha GOTCHA Gotcha
              VERSION 2.4.3
              GIT https://github.com/JaeseungYeom/GOTCHA.git
              TAG v1.0.9
              #GIT https://github.com/LLNL/GOTCHA.git
              #TAG 56def6fd26e436f01fb7831f784d0f9b1347904b
              REQUIRED
              #DIAG
              VARS "GOTCHA_ENABLE_TESTING OFF BOOL"
                   "CMAKE_INSTALL_LIBDIR ${BRAHMA_LIBDIR} PATH")


# Propagate up one more level to top-level CMakeLists.txt
set(gotcha_POPULATED    "${gotcha_POPULATED}"    PARENT_SCOPE)
set(gotcha_INCLUDE_DIRS "${gotcha_INCLUDE_DIRS}" PARENT_SCOPE)
set(gotcha_LIBRARIES    "${gotcha_LIBRARIES}"    PARENT_SCOPE)
set(gotcha_FOUND        "${gotcha_FOUND}"        PARENT_SCOPE)


get_target_property(_gotcha_imported gotcha IMPORTED)
if (NOT _gotcha_imported OR _gotcha_imported MATCHES "NOTFOUND")
    # GOTCHA uses GNU-specific extensions. So it needs to be
    # compiled with -std=gnu11 instead of -std=c11.
    set_target_properties(gotcha PROPERTIES C_EXTENSIONS ON)
    # Setting gotcha include dirs
    target_include_directories(gotcha PUBLIC
        $<BUILD_INTERFACE:${gotcha_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${gotcha_SOURCE_DIR}/include>
    )
endif ()
