find_package(LLVM REQUIRED CONFIG)
find_package(Python 3 REQUIRED)

if (LLVM_FOUND)
    if (Python_FOUND)
        set(GENERATED_FILES
            ${CMAKE_SOURCE_DIR}/include/brahma/interface/hdf5.h
            ${CMAKE_SOURCE_DIR}/src/brahma/interface/hdf5.cpp
        )
        add_custom_command(
            OUTPUT ${GENERATED_FILES}
            COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/generate_interfaces.py
                --libclang-path ${LLVM_LIBRARY_DIRS}/libclang.so
                --hdf5-header-path ${HDF5_INCLUDE_DIRS}/hdf5.h
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating interfaces..."
            VERBATIM
        )
        add_custom_target(generate_interfaces ALL DEPENDS ${GENERATED_FILES})
        add_dependencies(brahma generate_interfaces)
    else()
        message(FATAL_ERROR "Python not found")
    endif()
else()
    message(FATAL_ERROR "LLVM not found")
endif()
