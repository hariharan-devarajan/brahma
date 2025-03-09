find_package(LLVM 14 REQUIRED CONFIG)
find_package(Python 3 REQUIRED)

set(COMMAND_ARGS "")
set(GENERATED_FILES "")

if(BRAHMA_BUILD_WITH_HDF5)
    find_package(HDF5 1.8 COMPONENTS CXX REQUIRED)
    list(APPEND COMMAND_ARGS
        --hdf5-header-path ${HDF5_INCLUDE_DIRS}/hdf5.h
        --hdf5-version 1.8
    )
    find_package(HDF5 1.12 COMPONENTS CXX REQUIRED)
    list(APPEND COMMAND_ARGS
        --hdf5-header-path ${HDF5_INCLUDE_DIRS}/hdf5.h
        --hdf5-version 1.12
    )
    find_package(HDF5 1.14 COMPONENTS CXX REQUIRED)
    list(APPEND COMMAND_ARGS
        --hdf5-header-path ${HDF5_INCLUDE_DIRS}/hdf5.h
        --hdf5-version 1.14
    )
    list(APPEND GENERATED_FILES
        ${CMAKE_SOURCE_DIR}/include/brahma/interface/hdf5.h
        ${CMAKE_SOURCE_DIR}/src/brahma/interface/hdf5.cpp
    )
endif()

if(BRAHMA_BUILD_WITH_MPI)
    find_package(MPI COMPONENTS CXX REQUIRED)
    list(APPEND COMMAND_ARGS
        --mpio-header-path ${MPI_CXX_INCLUDE_PATH}
    )
    list(APPEND GENERATED_FILES
        ${CMAKE_SOURCE_DIR}/include/brahma/interface/mpiio.h
        ${CMAKE_SOURCE_DIR}/src/brahma/interface/mpiio.cpp
    )
endif()

add_custom_target(generate_interfaces ALL 
    COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/generate_interfaces.py
        --libclang-path ${LLVM_LIBRARY_DIRS}/libclang.so
        ${COMMAND_ARGS}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating interfaces..."
    VERBATIM
)

