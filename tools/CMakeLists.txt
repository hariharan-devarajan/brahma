find_package(LLVM REQUIRED CONFIG)
find_package(Python 3 REQUIRED)

set(COMMAND_ARGS "")
set(GENERATED_FILES "")

if(BRAHMA_BUILD_WITH_HDF5)
    find_package(HDF5 COMPONENTS CXX REQUIRED)
    list(APPEND COMMAND_ARGS
        --hdf5-header-path ${HDF5_INCLUDE_DIRS}/hdf5.h
    )
    list(APPEND GENERATED_FILES
        ${CMAKE_SOURCE_DIR}/include/brahma/interface/hdf5.h
        ${CMAKE_SOURCE_DIR}/src/brahma/interface/hdf5.cpp
    )
endif()

add_custom_command(
    OUTPUT ${GENERATED_FILES}
    COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/generate_interfaces.py
        --libclang-path ${LLVM_LIBRARY_DIRS}/libclang.so
        ${COMMAND_ARGS}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating interfaces..."
    VERBATIM
)
add_custom_target(generate_interfaces ALL DEPENDS ${GENERATED_FILES})
