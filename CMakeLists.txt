cmake_minimum_required(VERSION 3.0)
project(brahma)# VERSION 1.0.0 DESCRIPTION "I/O interceptor library in CPP using Gotcha")
#------------------------------------------------------------------------------
# Version information
#------------------------------------------------------------------------------
set(BRAHMA_VERSION_MAJOR "0")
set(BRAHMA_VERSION_MINOR "0")
set(BRAHMA_VERSION_PATCH "1")
set(BRAHMA_PACKAGE ${PROJECT_NAME})
set(BRAHMA_PACKAGE_NAME ${PROJECT_NAME})
set(BRAHMA_PACKAGE_VERSION "${BRAHMA_VERSION_MAJOR}.${BRAHMA_VERSION_MINOR}.${BRAHMA_VERSION_PATCH}")
set(BRAHMA_PACKAGE_VERSION_MAJOR "${BRAHMA_VERSION_MAJOR}.${BRAHMA_VERSION_MINOR}")
set(BRAHMA_PACKAGE_VERSION_MINOR "${BRAHMA_VERSION_PATCH}")
set(BRAHMA_PACKAGE_STRING "${BRAHMA_PACKAGE_NAME} ${BRAHMA_PACKAGE_VERSION}")
set(BRAHMA_PACKAGE_TARNAME "${BRAHMA_PACKAGE}")

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/dependency/.spack-env/view ${CMAKE_BINARY_DIR}/lib/cmake)

#------------------------------------------------------------------------------
# Build options
#------------------------------------------------------------------------------
option(BUILD_WITH_MPI "Build with mpi and mpiio interception libraries." OFF)



set(CMAKE_CXX_STANDARD 17)
set(BRAHMA_CMAKE_DIR ${CMAKE_SOURCE_DIR}/CMake ${CMAKE_BINARY_DIR}/lib/cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${BRAHMA_CMAKE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(BRAHMA_MPI_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/brahma/interface/mpiio.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/brahma/mpi.cpp)
set(BRAHMA_MPI_INCLUDE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/interface/mpiio.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/mpi.h)

set(BRAHMA_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/brahma/brahma.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/brahma/interface/posix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/brahma/interface/stdio.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/brahma/interceptor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/brahma/interface/interface.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/brahma/interface/interface_utility.cpp)
set(BRAHMA_PUBLIC_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/interceptor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/brahma.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/interface/interface.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/interface/interface_utility.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/enumeration.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/singleton.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/interface/posix.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/brahma/interface/stdio.h)
if(BUILD_WITH_MPI)
    set(BRAHMA_SRC ${BRAHMA_SRC} ${BRAHMA_MPI_SRC})
    set(BRAHMA_PUBLIC_INCLUDE ${BRAHMA_PUBLIC_INCLUDE} ${BRAHMA_MPI_INCLUDE})
    add_definitions(-DCOMPILE_MPI)
endif()
set(BRAHMA_PRIVATE_INCLUDE)
add_library(${PROJECT_NAME} SHARED)
message(STATUS ${CMAKE_PREFIX_PATH})

target_sources(${PROJECT_NAME}
        PRIVATE
        ${BRAHMA_SRC}
        )
target_include_directories(${PROJECT_NAME}
        PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )

#------------------------------------------------------------------------------
# Setup install and output Directories
#------------------------------------------------------------------------------
if (NOT BRAHMA_INSTALL_BIN_DIR)
    set(BRAHMA_INSTALL_BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
    message(STATUS ${BRAHMA_INSTALL_BIN_DIR})
endif ()
if (NOT BRAHMA_INSTALL_LIB_DIR)
    set(BRAHMA_INSTALL_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib)
endif ()
if (NOT BRAHMA_INSTALL_INCLUDE_DIR)
    set(BRAHMA_INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)
endif ()
if (NOT BRAHMA_INSTALL_DATA_DIR)
    set(BRAHMA_INSTALL_DATA_DIR ${CMAKE_INSTALL_PREFIX}/share)
endif ()

if (NOT CMAKE_INSTALL_RPATH)
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif ()

#------------------------------------------------------------------------------
if (NOT BRAHMA_EXTERNALLY_CONFIGURED)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
            ${CMAKE_BINARY_DIR}/bin CACHE PATH "Single Directory for all Executables."
            )

    set(CMAKE_INCLUDE_OUTPUT_DIRECTORY
            ${CMAKE_BINARY_DIR}/include CACHE PATH "Store the headers."
            )
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
            ${CMAKE_BINARY_DIR}/lib CACHE PATH "Single Directory for all Libraries"
            )
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
            ${CMAKE_BINARY_DIR}/lib CACHE PATH "Single Directory for all static libraries."
            )
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

if (NOT "${CMAKE_CXX_STANDARD}")
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif ()

#-----------------------------------------------------------------------------
# Targets built within this project are exported at Install time for use
# by other projects.
#-----------------------------------------------------------------------------
if (NOT BRAHMA_EXPORTED_TARGETS)
    set(BRAHMA_EXPORTED_TARGETS "${PROJECT_NAME}-targets")
endif ()

set(BRAHMA_LIBTYPE SHARED)
set_target_properties(${libtarget}
        PROPERTIES
        DEBUG_OUTPUT_NAME ${LIB_DEBUG_NAME}
        RELEASE_OUTPUT_NAME ${LIB_RELEASE_NAME}
        MINSIZEREL_OUTPUT_NAME ${LIB_RELEASE_NAME}
        RELWITHDEBINFO_OUTPUT_NAME ${LIB_RELEASE_NAME}
        VERSION ${LIB_VERSION}
        SOVERSION ${LIB_VERSION}
        )

include(GNUInstallDirs)
# the variant with PUBLIC_HEADER property unfortunately does not preserve the folder structure
#set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")
# so instead we iterate through public headers and install them "manually"
foreach (header ${BRAHMA_PUBLIC_INCLUDE})
    file(RELATIVE_PATH header_file_path "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}" "${header}")
    get_filename_component(header_directory_path "${header_file_path}" DIRECTORY)
    install(
            FILES ${header}
            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${header_directory_path}"
    )
    file(COPY ${header}
            DESTINATION "${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/${header_directory_path}")
endforeach ()
#-----------------------------------------------------------------------------
# Configure the config.cmake file for the build directory
#-----------------------------------------------------------------------------
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/CMake/${PROJECT_NAME}-config.cmake.build.in
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/${PROJECT_NAME}/${PROJECT_NAME}-config.cmake @ONLY
)
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/CMake/${PROJECT_NAME}-config.cmake.install.in
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/${PROJECT_NAME}/install/${PROJECT_NAME}-config.cmake @ONLY
)
install(
        FILES
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/${PROJECT_NAME}/install/${PROJECT_NAME}-config.cmake
        DESTINATION
        ${BRAHMA_INSTALL_LIB_DIR}/cmake/${PROJECT_NAME}
)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
#-----------------------------------------------------------------------------
# Configure the ${PROJECT_NAME}-config-version .cmake file for the install directory
#-----------------------------------------------------------------------------
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/CMake/${PROJECT_NAME}-config-version.cmake.in
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/${PROJECT_NAME}/${PROJECT_NAME}-config-version.cmake @ONLY
)

install(
        FILES
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/${PROJECT_NAME}/${PROJECT_NAME}-config-version.cmake
        DESTINATION
        ${BRAHMA_INSTALL_LIB_DIR}/cmake/${PROJECT_NAME}
)

install(
        TARGETS
        ${PROJECT_NAME}
        EXPORT
        ${BRAHMA_EXPORTED_TARGETS}
        LIBRARY DESTINATION ${BRAHMA_INSTALL_LIB_DIR}
        ARCHIVE DESTINATION ${BRAHMA_INSTALL_LIB_DIR}
        RUNTIME DESTINATION ${BRAHMA_INSTALL_BIN_DIR}
)
export(EXPORT ${BRAHMA_EXPORTED_TARGETS}
        FILE "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/${PROJECT_NAME}/${PROJECT_NAME}Targets.cmake")
install(EXPORT
        ${BRAHMA_EXPORTED_TARGETS}
        DESTINATION
        ${BRAHMA_INSTALL_LIB_DIR}/cmake/${PROJECT_NAME}
        FILE
        ${BRAHMA_EXPORTED_TARGETS}.cmake
        )
set(DEPENDENCY_LIB)

find_package(cpp-logger 0.0.1 REQUIRED)
if (${CPP_LOGGER_FOUND})
    message(STATUS "[Brahma] found cpp-logger at ${CPP_LOGGER_INCLUDE_DIRS}")
    include_directories(${CPP_LOGGER_INCLUDE_DIRS})
    set(DEPENDENCY_LIB ${DEPENDENCY_LIB} ${CPP_LOGGER_LIBRARIES})
else ()
    message(FATAL_ERROR "-- [Brahma] cpp-logger is needed for ${PROJECT_NAME} build")
endif ()

# find Gotcha
find_package(gotcha 2.1.2 REQUIRED)
if (${gotcha_FOUND})
    message(STATUS "[Brahma] found gotcha at ${gotcha_INCLUDE_DIRS}")
    include_directories(${gotcha_INCLUDE_DIRS})
    set(DEPENDENCY_LIB ${DEPENDENCY_LIB} ${gotcha_LIBRARIES})
else ()
    message(FATAL_ERROR "-- [Brahma] gotcha is needed for ${PROJECT_NAME} build")
endif ()
if(BUILD_WITH_MPI)
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


target_link_libraries(${PROJECT_NAME} ${DEPENDENCY_LIB})

option(BRAHMA_BUILD_TEST "Build the unit tests" OFF)
if (BRAHMA_BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
endif ()