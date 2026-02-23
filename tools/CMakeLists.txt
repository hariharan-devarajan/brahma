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

# Use discover_and_generate.sh for package discovery
set(GENERATE_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/discover_and_generate.sh")

add_custom_target(generate_interfaces ALL 
    COMMAND ${GENERATE_SCRIPT} --select-all --quiet
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating interfaces using discover_and_generate.sh..."
    VERBATIM
)

