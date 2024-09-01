cmake_minimum_required(VERSION 3.10.2)
#------------------------------------------------------------------------------
# Version information
#------------------------------------------------------------------------------


set(BRAHMA_VERSION_MAJOR "1")
set(BRAHMA_VERSION_MINOR "0")
set(BRAHMA_VERSION_PATCH "0")
set(BRAHMA_PACKAGE ${PROJECT_NAME})
set(BRAHMA_PACKAGE_NAME ${PROJECT_NAME})
set(BRAHMA_PACKAGE_VERSION "${BRAHMA_VERSION_MAJOR}.${BRAHMA_VERSION_MINOR}.${BRAHMA_VERSION_PATCH}")
set(BRAHMA_PACKAGE_VERSION_MAJOR "${BRAHMA_VERSION_MAJOR}.${BRAHMA_VERSION_MINOR}")
set(BRAHMA_PACKAGE_VERSION_MINOR "${BRAHMA_VERSION_PATCH}")
set(BRAHMA_PACKAGE_STRING "${BRAHMA_PACKAGE_NAME} ${BRAHMA_PACKAGE_VERSION}")
set(BRAHMA_PACKAGE_TARNAME "${BRAHMA_PACKAGE}")
set(BRAHMA_LIBTOOL_VERSION "${BRAHMA_PACKAGE_VERSION}")

set(BRAHMA_VERSION "(0, 0, 5)")

project(brahma LANGUAGES C CXX)

# Convenience defines
string(TOUPPER "${PROJECT_NAME}" UPPER_PROJECT_NAME)
string(TOLOWER "${PROJECT_NAME}" LOWER_PROJECT_NAME)

#------------------------------------------------------------------------------
# Internal Includes for header and libraries
#------------------------------------------------------------------------------
# Get installation directories -- these get used in various places;
# best to just make them available
option (BRAHMA_LIBDIR_AS_LIB OFF)
if (NOT BRAHMA_LIBDIR_AS_LIB)
    include(GNUInstallDirs)
endif ()
#
if (CMAKE_INSTALL_LIBDIR)
   message(STATUS "CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR}")
   set(BRAHMA_LIBDIR ${CMAKE_INSTALL_LIBDIR})
   set(BRAHMA_INSTALL_INCLUDE_DIR
       ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR})
   set(BRAHMA_INSTALL_DOCDIR
       ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DOCDIR})
   set(BRAHMA_INSTALL_SYSCONFDIR
       ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_SYSCONFDIR}/modulefiles)
else ()
   set(BRAHMA_LIBDIR "lib")
   set(BRAHMA_INSTALL_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/include")
   set(BRAHMA_INSTALL_DOCDIR "${CMAKE_INSTALL_PREFIX}/doc")
   set(BRAHMA_INSTALL_SYSCONFDIR "${CMAKE_INSTALL_PREFIX}/etc/modulefiles")
   message(STATUS "BRAHMA_LIBDIR set to ${BRAHMA_LIBDIR}")
endif ()

#------------------------------------------------------------------------------
# Internal Paths for cmake libraries and Setup install and output Directories
#------------------------------------------------------------------------------
# This sets where to look for dependent libraries
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_BINARY_DIR} ${CMAKE_INSTALL_PREFIX})
# This sets where to look for dependent library's cmake files
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR}/${BRAHMA_LIBDIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR}/share/cmake)

#------------------------------------------------------------------------------
if (NOT BRAHMA_EXTERNALLY_CONFIGURED)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin CACHE PATH "Single Directory for all Executables.")
    set(CMAKE_INCLUDE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/include CACHE PATH "Store the headers.")
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${BRAHMA_LIBDIR} CACHE PATH "Single Directory for all Libraries")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${BRAHMA_LIBDIR} CACHE PATH "Single Directory for all static libraries.")
endif ()

#-----------------------------------------------------------------------------
# Targets built within this project are exported at Install time for use
# by other projects.
#-----------------------------------------------------------------------------
if (NOT BRAHMA_EXPORTED_TARGETS)
    set(BRAHMA_EXPORTED_TARGETS "brahma-targets")
endif ()
#------------------------------------------------------------------------------
# Build options
#------------------------------------------------------------------------------
# option(ENABLE_BRAHMA_DEBUG "Include debugging prints and logging" OFF) # This is not needed as we have CMAKE_BUILD_TYPE
# This is verbose, maybe an alternate might help simplify
#option(BUILD_URPC "Build BRAHMA's URPC code" OFF)
#option(ENABLE_PERFFLOW "Build with PerfFlow Aspect support" OFF)
#option(ENABLE_UCX_DTL "Build BRAHMA's UCX data transport layer" OFF)

# This option is off by default because non-developers should not use
# this option under normal circumstances.
option(BRAHMA_WARNINGS_AS_ERRORS "Build with warnings promoted to errors." OFF)
mark_as_advanced(BRAHMA_WARNINGS_AS_ERRORS)

option (BRAHMA_USE_CLANG_LIBCXX OFF)
if (BRAHMA_USE_CLANG_LIBCXX)
    set (GCC_TOOLCHAIN "")
endif (BRAHMA_USE_CLANG_LIBCXX)

# Public
option(BRAHMA_BUILD_WITH_HDF5 "Build with HDF5 interception libraries." OFF)
option(BRAHMA_BUILD_WITH_MPI "Build with mpi and mpiio interception libraries." OFF)
option(BRAHMA_BUILD_DEPENDENCIES "Build Dependencies for Brahma" OFF)
option(BRAHMA_GENERATE_INTERFACES "Generate interfaces for Brahma" OFF)
option(BRAHMA_INSTALL_DEPENDENCIES "Install dependencies for Brahma" OFF)

if(BRAHMA_BUILD_WITH_HDF5)
    set(BRAHMA_ENABLE_HDF5 1)
endif()

if(BRAHMA_BUILD_WITH_MPI)
    set(BRAHMA_ENABLE_MPI 1)
endif()

# Profiling and logging
set(BRAHMA_LOGGER "NONE" CACHE STRING "Logger to use for BRAHMA")
set_property(CACHE BRAHMA_LOGGER PROPERTY STRINGS CPP_LOGGER NONE)
set(BRAHMA_LOGGER_LEVEL "NONE" CACHE STRING "Logging level to use for BRAHMA")
set_property(CACHE BRAHMA_LOGGER_LEVEL PROPERTY STRINGS TRACE DEBUG INFO WARN ERROR NONE)

# Testing
option (BRAHMA_ENABLE_TESTING "Enable tests for BRAHMA." OFF)

#------------------------------------------------------------------------------
# Compiler setup
#------------------------------------------------------------------------------
include(ExternalProject)
# It requires include(GNUInstallDirs) before if that is needed
include(SetupCompiler)

#------------------------------------------------------------------------------
# Build Type based configurations
#------------------------------------------------------------------------------

if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release") # Setting default as Release
endif()

if(BRAHMA_LOGGER STREQUAL "CPP_LOGGER")
    set(BRAHMA_LOGGER_CPP_LOGGER 1)
endif()

function(check_logger)
endfunction(check_logger)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (BRAHMA_LOGGER STREQUAL "NONE")
        message(STATUS "[${PROJECT_NAME}] disabling logger as no logger is selected")
        set(BRAHMA_LOGGER_NO_LOG 1)
    else()
        if (BRAHMA_LOGGER_LEVEL STREQUAL "NONE")
          set(BRAHMA_LOGGER_LEVEL "DEBUG")
        endif()
        
        if (BRAHMA_LOGGER_LEVEL STREQUAL "TRACE")
          set(BRAHMA_LOGGER_LEVEL_ERROR 1)
          set(BRAHMA_LOGGER_LEVEL_WARN 1)
          set(BRAHMA_LOGGER_LEVEL_INFO 1)
          set(BRAHMA_LOGGER_LEVEL_DEBUG 1)
          set(BRAHMA_LOGGER_LEVEL_TRACE 1)
        elseif (BRAHMA_LOGGER_LEVEL STREQUAL "DEBUG")
          set(BRAHMA_LOGGER_LEVEL_ERROR 1)
          set(BRAHMA_LOGGER_LEVEL_WARN 1)
          set(BRAHMA_LOGGER_LEVEL_INFO 1)
          set(BRAHMA_LOGGER_LEVEL_DEBUG 1)
        elseif(BRAHMA_LOGGER_LEVEL STREQUAL "ERROR")
          set(BRAHMA_LOGGER_LEVEL_ERROR 1)
        elseif(BRAHMA_LOGGER_LEVEL STREQUAL "WARN")
          set(BRAHMA_LOGGER_LEVEL_ERROR 1)
          set(BRAHMA_LOGGER_LEVEL_WARN 1)
        elseif(BRAHMA_LOGGER_LEVEL STREQUAL "INFO")
          set(BRAHMA_LOGGER_LEVEL_ERROR 1)
          set(BRAHMA_LOGGER_LEVEL_WARN 1)
          set(BRAHMA_LOGGER_LEVEL_INFO 1)
        else()
          set(BRAHMA_LOGGER_NO_LOG 1)
        endif()
    endif()
else()
  if (BRAHMA_LOGGER_LEVEL STREQUAL "NONE")
    set(BRAHMA_LOGGER_LEVEL "WARN")
  endif()
        
  if (BRAHMA_LOGGER_LEVEL STREQUAL "TRACE")
    set(BRAHMA_LOGGER_LEVEL_ERROR 1)
    set(BRAHMA_LOGGER_LEVEL_WARN 1)
    set(BRAHMA_LOGGER_LEVEL_INFO 1)
    set(BRAHMA_LOGGER_LEVEL_DEBUG 1)
    set(BRAHMA_LOGGER_LEVEL_TRACE 1)
  elseif (BRAHMA_LOGGER_LEVEL STREQUAL "DEBUG")
    set(BRAHMA_LOGGER_LEVEL_ERROR 1)
    set(BRAHMA_LOGGER_LEVEL_WARN 1)
    set(BRAHMA_LOGGER_LEVEL_INFO 1)
    set(BRAHMA_LOGGER_LEVEL_DEBUG 1)
  elseif(BRAHMA_LOGGER_LEVEL STREQUAL "ERROR")
    set(BRAHMA_LOGGER_LEVEL_ERROR 1)
  elseif(BRAHMA_LOGGER_LEVEL STREQUAL "WARN")
    set(BRAHMA_LOGGER_LEVEL_ERROR 1)
    set(BRAHMA_LOGGER_LEVEL_WARN 1)
  elseif(BRAHMA_LOGGER_LEVEL STREQUAL "INFO")
    set(BRAHMA_LOGGER_LEVEL_ERROR 1)
    set(BRAHMA_LOGGER_LEVEL_WARN 1)
    set(BRAHMA_LOGGER_LEVEL_INFO 1)
  else()
    set(BRAHMA_LOGGER_NO_LOG 1)
  endif()
endif()

if (NOT DEFINED BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ON)
endif ()
#------------------------------------------------------------------------------
# Disallow in-source build
#------------------------------------------------------------------------------
if ("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR
            "${PROJECT_NAME} requires an out of source Build. "
            "Please create a separate binary directory and run CMake there.")
endif ()
#------------------------------------------------------------------------------
# Set a default build type if none was specified
#------------------------------------------------------------------------------
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
            "MinSizeRel" "RelWithDebInfo")
endif ()


function(brahma_install_headers public_headers current_dir)
    #message("-- [${PROJECT_NAME}] " "installing headers ${public_headers}")
    foreach (header ${public_headers})
        file(RELATIVE_PATH header_file_path "${PROJECT_SOURCE_DIR}/src" "${header}")
        #message("-- [${PROJECT_NAME}] " "installing header ${header_file_path}")
        get_filename_component(header_directory_path "${header_file_path}" DIRECTORY)
        install(
                FILES ${header}
                DESTINATION "include/${header_directory_path}"
        )
        file(COPY ${header}
                DESTINATION "${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/${header_directory_path}")
    endforeach ()
    set(INCLUDE_INSTALL_DIRS ${public_headers})
endfunction()


#------------------------------------------------------------------------------
# Dependencies
#------------------------------------------------------------------------------

# Install Dependencies
# =============================================================================
if (BRAHMA_BUILD_DEPENDENCIES)
  add_subdirectory(dependency)
else()
#-----------------------------------------------------------------------------
# Source for BRAHMA
#-----------------------------------------------------------------------------
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
include_directories(${CMAKE_SOURCE_DIR}/include)  # public header
include_directories(${CMAKE_SOURCE_DIR}/src)  # private header
include_directories(${CMAKE_BINARY_DIR}/include)  # build header

set(BRAHMA_HDF5_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/brahma/interface/hdf5.cpp)
set(BRAHMA_HDF5_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/interface/hdf5.h)

set(BRAHMA_MPI_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/brahma/interface/mpiio.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/brahma/mpi.cpp)
set(BRAHMA_MPI_INCLUDE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/interface/mpiio.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/mpi.h)

set(BRAHMA_SRC  ${CMAKE_CURRENT_SOURCE_DIR}/src/brahma/brahma.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/brahma/interface/posix.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/brahma/interface/stdio.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/brahma/interceptor.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/brahma/interface/interface.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/brahma/interface/interface_utility.cpp)
set(BRAHMA_PRIVATE_HEADER  )
set(BRAHMA_PUBLIC_HEADER        ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/logging.h
                                ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/interceptor.h
                                ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/brahma.h
                                ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/interface/interface.h
                                ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/interface/interface_utility.h
                                ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/enumeration.h
                                ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/singleton.h
                                ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/interface/posix.h
                                ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/interface/stdio.h)
set(BRAHMA_SRC_PRIVATE )

if(BRAHMA_BUILD_WITH_HDF5)
  set(BRAHMA_SRC ${BRAHMA_SRC} ${BRAHMA_HDF5_SRC})
  set(BRAHMA_PUBLIC_HEADER ${BRAHMA_PUBLIC_HEADER} ${BRAHMA_HDF5_INCLUDE})
endif()

if(BRAHMA_BUILD_WITH_MPI)
  set(BRAHMA_SRC ${BRAHMA_SRC} ${BRAHMA_MPI_SRC})
  set(BRAHMA_PUBLIC_HEADER ${BRAHMA_PUBLIC_HEADER} ${BRAHMA_MPI_INCLUDE})
endif()

add_library(${PROJECT_NAME} SHARED ${BRAHMA_SRC} ${BRAHMA_PUBLIC_HEADER} ${BRAHMA_PRIVATE_HEADER})

set_target_properties(${PROJECT_NAME} PROPERTIES
    LINKER_LANGUAGE CXX
    VERSION ${BRAHMA_LIBTOOL_VERSION}
    SOVERSION 1
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/brahma.h)
target_compile_definitions(${PROJECT_NAME} PUBLIC BRAHMA_HAS_CONFIG)
brahma_install_headers("${BRAHMA_PUBLIC_HEADER};${BRAHMA_SRC_PRIVATE}" ${CMAKE_CURRENT_SOURCE_DIR})

# Required Dependencies
# =============================================================================
set(DEPENDENCY_LIB )
# find Gotcha
find_package(gotcha 2.1.2 REQUIRED)
if (${gotcha_FOUND})
    message(STATUS "[Brahma] found gotcha at ${gotcha_INCLUDE_DIRS}")
    include_directories(${gotcha_INCLUDE_DIRS})
    set(DEPENDENCY_LIB ${DEPENDENCY_LIB} ${gotcha_LIBRARIES})
else ()
    message(FATAL_ERROR "-- [Brahma] gotcha is needed for ${PROJECT_NAME} build")
endif ()

# Optional Dependencies
# =============================================================================
if(BRAHMA_BUILD_WITH_HDF5)
    # find HDF5
    find_package(HDF5 COMPONENTS CXX REQUIRED)
    if (HDF5_FOUND)
        message(STATUS "[Brahma] found hdf5.h at ${HDF5_CXX_INCLUDE_DIRS}")
        include_directories(${HDF5_CXX_INCLUDE_DIRS})
        set(DEPENDENCY_LIB ${DEPENDENCY_LIB} ${HDF5_CXX_LIBRARIES})
    else ()
        message(FATAL_ERROR "-- [Brahma] HDF5 is needed for ${PROJECT_NAME} build")
    endif ()
endif()

if(BRAHMA_BUILD_WITH_MPI)
    # find MPI
    find_package(MPI COMPONENTS CXX REQUIRED)
    if (MPI_FOUND)
        message(STATUS "[Brahma] found mpi.h at ${MPI_CXX_INCLUDE_DIRS}")
        include_directories(${MPI_CXX_INCLUDE_DIRS})
        set(DEPENDENCY_LIB ${DEPENDENCY_LIB} ${MPI_CXX_LIBRARIES})
    else ()
        message(FATAL_ERROR "-- [Brahma] mpi is needed for ${PROJECT_NAME} build")
    endif ()
endif()

if (BRAHMA_LOGGER STREQUAL "CPP_LOGGER")
    find_package(cpp-logger 1.0.0 REQUIRED
                 HINTS ${CPP_LOGGER_DIR} ${cpp-logger_DIR}
                       ${CPP_LOGGER_PATH} ${cpp-logger_PATH}
                       $ENV{CPP_LOGGER_DIR} $ENV{cpp-logger_DIR}
                       $ENV{CPP_LOGGER_PATH} $ENV{cpp-logger_PATH})
    if (${cpp-logger_FOUND})
        message(STATUS "[${PROJECT_NAME}] found cpp-logger at ${CPP_LOGGER_INCLUDE_DIRS}")
        include_directories(SYSTEM ${CPP_LOGGER_INCLUDE_DIRS})
        set(DEPENDENCY_LIB ${DEPENDENCY_LIB} ${CPP_LOGGER_LIBRARIES})
    else ()
        message(FATAL_ERROR "-- [${PROJECT_NAME}] cpp-logger is not found but selected in cmake options for ${PROJECT_NAME} build")
    endif ()
endif()

target_link_libraries(${PROJECT_NAME} ${DEPENDENCY_LIB})

if (BRAHMA_GENERATE_INTERFACES)
  add_subdirectory(tools)
endif()

install(
        TARGETS ${PROJECT_NAME}
        EXPORT ${BRAHMA_EXPORTED_TARGETS}
        LIBRARY DESTINATION ${BRAHMA_INSTALL_LIB_DIR}
        ARCHIVE DESTINATION ${BRAHMA_INSTALL_LIB_DIR}
        RUNTIME DESTINATION ${BRAHMA_INSTALL_BIN_DIR}
)
#-----------------------------------------------------------------------------
# Testing
#-----------------------------------------------------------------------------

#cmake_policy(SET CMP0079 NEW) # In case that we need more control over the target building order

if(BRAHMA_ENABLE_TESTING)
  enable_testing()
  set(TEST_LIBS )
  add_subdirectory(test)
endif()

#-----------------------------------------------------------------------------
# Configure the config.cmake file for the build directory
#-----------------------------------------------------------------------------
include(CMakePackageConfigHelpers)
configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/configure_files/${PROJECT_NAME}-config.cmake.build.in
        "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
        INSTALL_DESTINATION  ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/${PROJECT_NAME}/${PROJECT_NAME}-config.cmake 
        PATH_VARS CMAKE_BINARY_DIR
)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/configure_files/${PROJECT_NAME}-config.cmake.install.in
        "${CMAKE_BINARY_DIR}/install/${PROJECT_NAME}-config.cmake"
        INSTALL_DESTINATION  ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/${PROJECT_NAME}/install/${PROJECT_NAME}-config.cmake
        PATH_VARS CMAKE_BINARY_DIR
)

# configure_file(
#         ${CMAKE_CURRENT_SOURCE_DIR}/cmake/configure_files/${PROJECT_NAME}-config.cmake.install.in
#         ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/${PROJECT_NAME}/install/${PROJECT_NAME}-config.cmake @ONLY
# )
install(
        FILES
        "${CMAKE_BINARY_DIR}/install/${PROJECT_NAME}-config.cmake"
        DESTINATION
        ${BRAHMA_LIBDIR}/cmake/${PROJECT_NAME}
)
#-----------------------------------------------------------------------------
# Configure the ${PROJECT_NAME}-config-version .cmake file for the install directory
#-----------------------------------------------------------------------------
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/configure_files/${PROJECT_NAME}-config-version.cmake.in
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/${PROJECT_NAME}/${PROJECT_NAME}-config-version.cmake @ONLY
)

install(
        FILES
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/${PROJECT_NAME}/${PROJECT_NAME}-config-version.cmake
        DESTINATION
        ${BRAHMA_LIBDIR}/cmake/${PROJECT_NAME}
)

export(EXPORT ${BRAHMA_EXPORTED_TARGETS}
        FILE "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/${PROJECT_NAME}/${PROJECT_NAME}Targets.cmake")

# Write the configure file
configure_file("${CMAKE_SOURCE_DIR}/cmake/configure_files/brahma_config.hpp.in"
               "${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/brahma/brahma_config.hpp" @ONLY)


################################################################
# Install BRAHMA
################################################################

include(CMakePackageConfigHelpers)

# Write the version file. This is independent of build/install tree.
write_basic_package_version_file(
  BrahmaConfigVersion.cmake
  VERSION "${BRAHMA_PACKAGE_VERSION}"
  COMPATIBILITY SameMajorVersion)

install(FILES
        "${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/brahma/brahma_config.hpp"
        DESTINATION
        ${BRAHMA_INSTALL_INCLUDE_DIR}/brahma)

install(EXPORT
        ${BRAHMA_EXPORTED_TARGETS}
        DESTINATION
        ${BRAHMA_LIBDIR}/cmake/${PROJECT_NAME}
        FILE
        ${BRAHMA_EXPORTED_TARGETS}.cmake
        )

# Install export
install(EXPORT ${BRAHMA_EXPORTED_TARGETS}
        NAMESPACE brahma::
        FILE BrahmaTargets.cmake
        DESTINATION "${BRAHMA_LIBDIR}/cmake/brahma")

# Install license and readme
install(FILES
        "${PROJECT_SOURCE_DIR}/NOTICE"
        "${PROJECT_SOURCE_DIR}/LICENSE"
        "${PROJECT_SOURCE_DIR}/README.md"
        DESTINATION
        ${BRAHMA_INSTALL_DOCDIR})

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/brahma-utils.cmake"
        DESTINATION "${BRAHMA_LIBDIR}/cmake/brahma")


###############################################################################
#                      Print out configuration summary
###############################################################################
include(brahma-utils)
if (CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
  set(BRAHMA_GNU_LINUX TRUE)
endif ()

# NOTE: message() outputs to stderr by default. We now use a string to
# maintain this information and then have cmake echo it to stdout. The
# only side effects are that if you use the CMake GUI, you won't see
# this output anymore (they only report stderr) and that if you add
# something to the list, you must remember your newline!
set(_str "\n== BRAHMA Configuration Summary ==\n\n")
string(APPEND _str "  PROJECT_SOURCE_DIR:   ${PROJECT_SOURCE_DIR}\n"
  "  PROJECT_BINARY_DIR:   ${PROJECT_BINARY_DIR}\n\n"
  "  CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}\n"
  "  CMAKE_BUILD_TYPE:     ${CMAKE_BUILD_TYPE}\n\n")
if (CMAKE_BUILD_TYPE MATCHES None)
  string(APPEND _str
    "  CXX FLAGS:            ${CMAKE_CXX_FLAGS}\n")
elseif (CMAKE_BUILD_TYPE MATCHES Release)
  string(APPEND _str
    "  CXX FLAGS:            ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}\n")
  string(APPEND _str
    "  C FLAGS:              ${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}\n")
elseif (CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
  string(APPEND _str
    "  CXX FLAGS:            ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}\n")
  string(APPEND _str
    "  C FLAGS:              ${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELWITHDEBINFO}\n")
elseif (CMAKE_BUILD_TYPE MATCHES Debug)
  string(APPEND _str
    "  CXX FLAGS:            ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}\n")
  string(APPEND _str
    "  C FLAGS:              ${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG}\n")
endif ()
string(APPEND _str
  "  DEPENDENCY_LIB:              ${DEPENDENCY_LIB}\n")
string(APPEND _str "\n")

string(APPEND _str
  "  BRAHMA_PACKAGE_VERSION:        ${BRAHMA_PACKAGE_VERSION}\n")
string(APPEND _str
  "  BRAHMA_GIT_VERSION:            ${BRAHMA_GIT_VERSION}\n")
string(APPEND _str
  "  BRAHMA_BUILD_WITH_HDF5:         ${BRAHMA_BUILD_WITH_HDF5}\n")
string(APPEND _str
  "  BRAHMA_BUILD_WITH_MPI:          ${BRAHMA_BUILD_WITH_MPI}\n")
if(BRAHMA_BUILD_WITH_MPI)
  string(APPEND _str
  "  MPIEXEC_EXECUTABLE:                ${MPIEXEC_EXECUTABLE}\n")
endif()
string(APPEND _str
  "  BRAHMA_PROFILER:               ${BRAHMA_PROFILER}\n")
string(APPEND _str
  "  BRAHMA_LOGGER:                 ${BRAHMA_LOGGER}\n")
string(APPEND _str
  "  BRAHMA_LOGGER_LEVEL:           ${BRAHMA_LOGGER_LEVEL}\n")
string(APPEND _str
  "  GLIBC_VERSION:               ${GLIBC_VERSION}\n")
string(APPEND _str
  "  TEST_LIBS:               ${TEST_LIBS}\n")

#Print the true/false variables
append_str_tf(_str
  BRAHMA_GNU_LINUX
  BRAHMA_BUILD_WITH_HDF5
  BRAHMA_BUILD_WITH_MPI
  BRAHMA_LIBDIR_AS_LIB
  BRAHMA_USE_CLANG_LIBCXX
  BRAHMA_WARNINGS_AS_ERRORS
  BRAHMA_ENABLE_TESTING
)
string(APPEND _str
  "\n== End BRAHMA Configuration Summary ==\n")

# Output to stdout
execute_process(COMMAND ${CMAKE_COMMAND} -E echo "${_str}")
set(_str)


###############################################################################
# Write a basic modulefile
###############################################################################

set(BRAHMA_MODULEFILE_NAME "brahma-${BRAHMA_PACKAGE_VERSION}.lua")
#  CACHE STRING
#  "The name of the BRAHMA modulefile to install. Must end in .lua.")

if (NOT (BRAHMA_MODULEFILE_NAME MATCHES ".+\.lua"))
  message(WARNING
    "BRAHMA_MODULEFILE_NAME must have extension \".lua\". Appending.")
  set(BRAHMA_MODULEFILE_NAME "${BRAHMA_MODULEFILE_NAME}.lua"
    CACHE STRING "" FORCE)
endif ()

configure_file(
  "${CMAKE_SOURCE_DIR}/cmake/configure_files/brahma_module.lua.in"
  "${CMAKE_BINARY_DIR}/brahma_module.lua.install"
  @ONLY)

install(FILES "${CMAKE_BINARY_DIR}/brahma_module.lua.install"
  RENAME "${BRAHMA_MODULEFILE_NAME}"
  DESTINATION
  "${BRAHMA_INSTALL_SYSCONFDIR}")
endif()