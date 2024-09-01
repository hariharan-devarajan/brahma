find_package(Clang REQUIRED CONFIG)
if(CLANG_VERSION_MAJOR LESS 14)
    message(FATAL_ERROR "Clang version 14 or above is required, found ${CLANG_PACKAGE_VERSION}")
endif()
if(Clang_FOUND)
    message(STATUS "Found Clang ${CLANG_PACKAGE_VERSION} ${CLANG_LIBRARY_DIRS}")
else()
    message(FATAL_ERROR "Clang not found")
endif()
find_package(Python 3 REQUIRED)
if(Python_FOUND)
    message(STATUS "Found Python ${Python_VERSION}: ${Python_EXECUTABLE}")
else()
    message(FATAL_ERROR "Python not found")
endif()

set(COMMAND_ARGS "")
set(GENERATED_FILES "")

if(BRAHMA_BUILD_WITH_HDF5)
    find_package(HDF5 1.8 QUIET)
    if(HDF5_FOUND)
        find_file(HDF5_HEADER_FILE 
            NAMES hdf5.h
            PATHS ${HDF5_INCLUDE_DIRS}
            NO_DEFAULT_PATH
        )

        if(NOT HDF5_HEADER_FILE)
            message(FATAL_ERROR "hdf5.h not found in ${HDF5_INCLUDE_DIRS}")
        endif()
        get_filename_component(HDF5_HEADER_PATH "${HDF5_HEADER_FILE}" DIRECTORY)
        list(APPEND COMMAND_ARGS
            --hdf5-header-path ${HDF5_HEADER_PATH}
            --hdf5-version 1.8
        )
    endif()
    find_package(HDF5 1.12 QUIET)
    if(HDF5_FOUND)
        find_file(HDF5_HEADER_FILE 
            NAMES hdf5.h
            PATHS ${HDF5_INCLUDE_DIRS}
            NO_DEFAULT_PATH
        )

        if(NOT HDF5_HEADER_FILE)
            message(FATAL_ERROR "hdf5.h not found in ${HDF5_INCLUDE_DIRS}")
        endif()
        get_filename_component(HDF5_HEADER_PATH "${HDF5_HEADER_FILE}" DIRECTORY)
        list(APPEND COMMAND_ARGS
            --hdf5-header-path ${HDF5_HEADER_PATH}
            --hdf5-version 1.12
        )
    endif()
    find_package(HDF5 1.14 QUIET)
    if(HDF5_FOUND)
        find_file(HDF5_HEADER_FILE 
            NAMES hdf5.h
            PATHS ${HDF5_INCLUDE_DIRS}
            NO_DEFAULT_PATH
        )

        if(NOT HDF5_HEADER_FILE)
            message(FATAL_ERROR "hdf5.h not found in ${HDF5_INCLUDE_DIRS}")
        endif()
        get_filename_component(HDF5_HEADER_PATH "${HDF5_HEADER_FILE}" DIRECTORY)
        list(APPEND COMMAND_ARGS
            --hdf5-header-path ${HDF5_HEADER_PATH}
            --hdf5-version 1.14
        )
    endif()
    list(APPEND GENERATED_FILES
        ${CMAKE_SOURCE_DIR}/include/brahma/interface/hdf5.h
        ${CMAKE_SOURCE_DIR}/src/brahma/interface/hdf5.cpp
    )
endif()

if(BRAHMA_BUILD_WITH_MPI)
    find_package(MPI COMPONENTS C REQUIRED)
    if (MPI_FOUND)
        # If MPI_ROOT is set, override include path and find libraries
        if(DEFINED MPI_ROOT)
            # Find mpi.h in MPI_ROOT/include
            find_file(MPI_HEADER_FILE 
                NAMES mpi.h
                PATHS "${MPI_ROOT}/include"
                NO_DEFAULT_PATH
            )
            if(NOT MPI_HEADER_FILE)
                message(FATAL_ERROR "mpi.h not found in ${MPI_ROOT}/include")
            endif()
            get_filename_component(MPI_HEADER_PATH "${MPI_HEADER_FILE}" DIRECTORY)
        else()
            set(MPI_HEADER_PATH "${MPI_C_INCLUDE_PATH}")
        endif()
        if(NOT MPI_HEADER_PATH)
            message(FATAL_ERROR "mpi.h not found in ${MPI_C_INCLUDE_PATH}")
        endif()
        list(APPEND COMMAND_ARGS
            --mpio-header-path ${MPI_HEADER_PATH}
        )
        list(APPEND GENERATED_FILES
            ${CMAKE_SOURCE_DIR}/include/brahma/interface/mpiio.h
            ${CMAKE_SOURCE_DIR}/src/brahma/interface/mpiio.cpp
        )
    endif()
endif()

# Find libclang library
find_library(LIBCLANG_PATH 
    NAMES clang libclang
    PATHS ${CLANG_LIBRARY_DIRS} ${LLVM_LIBRARY_DIRS}
    PATH_SUFFIXES lib
    NO_DEFAULT_PATH
)

if(NOT LIBCLANG_PATH)
    find_library(LIBCLANG_PATH 
        NAMES clang libclang
        PATHS /usr/lib /usr/local/lib
        PATH_SUFFIXES llvm llvm-14 llvm-15 llvm-16 llvm-17 llvm-18
    )
endif()

if(LIBCLANG_PATH)
    message(STATUS "Found libclang: ${LIBCLANG_PATH}")
else()
    message(FATAL_ERROR "libclang not found in LLVM library directories: ${CLANG_LIBRARY_DIRS}")
endif()

add_custom_target(generate_interfaces ALL 
    COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/generate_interfaces.py
        --libclang-path ${LIBCLANG_PATH} --with-tests
        ${COMMAND_ARGS}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating interfaces..."
    VERBATIM
)

