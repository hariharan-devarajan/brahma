#ifndef BRAHMA_CONFIG_HPP
#define BRAHMA_CONFIG_HPP

/* Version string for BRAHMA */
#define BRAHMA_PACKAGE_VERSION "4.1.2"
#define BRAHMA_GIT_VERSION v1.0.10-1-g3d54a76

#define BRAHMA_GET_VERSION(MAJOR, MINOR, PATCH) (MAJOR * 100000 + MINOR * 100 + PATCH)
#define BRAHMA_VERSION (BRAHMA_GET_VERSION (1, 0, 10))
#define BRAHMA_VERSION_MAJOR (BRAHMA_VERSION / 100000)
#define BRAHMA_VERSION_MINOR ((BRAHMA_VERSION / 100) % 1000)
#define BRAHMA_VERSION_PATCH (BRAHMA_VERSION % 100)


/* Compiler used */
#define CMAKE_BUILD_TYPE "Debug"

#define CMAKE_C_COMPILER "/opt/cray/pe/craype/2.7.35/bin/cc"
#define CMAKE_C_FLAGS " -fPIC -Wall -Wextra -pedantic -Wno-unused-parameter -Wno-deprecated-declarations -fsanitize=address -fno-omit-frame-pointer -fsanitize-recover=address"
#define CMAKE_C_FLAGS_DEBUG "-g"
#define CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG"
#define CMAKE_C_FLAGS_RELEASE " -fPIC -Wall -Wextra -pedantic -Wno-unused-parameter -Wno-deprecated-declarations -fsanitize=address -fno-omit-frame-pointer -fsanitize-recover=address_RELEASE"

#define CMAKE_CXX_COMPILER "/opt/cray/pe/craype/2.7.35/bin/CC"
#define CMAKE_CXX_FLAGS " -fPIC -Wall -Wextra -pedantic -Wno-unused-parameter -Wnon-virtual-dtor -Wno-deprecated-declarations -fsanitize=address -fno-omit-frame-pointer -fsanitize-recover=address"
#define CMAKE_CXX_FLAGS_DEBUG "-g"
#define CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG"
#define CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG"

/* #undef CMAKE_C_SHARED_LIBRARY_FLAGS */
/* #undef CMAKE_CXX_SHARED_LIBRARY_FLAGS */

/* Macro flags */
/* #undef BRAHMA_GNU_LINUX */
#define BRAHMA_HAS_STD_FILESYSTEM 1
#define BRAHMA_HAS_STD_FSTREAM_FD 1
#define BRAHMA_ENABLE_HDF5 1
#define BRAHMA_ENABLE_MPI 1
// Logger
/* #undef BRAHMA_LOGGER_CPP_LOGGER */
// Logger level
#define BRAHMA_LOGGER_NO_LOG 1
/* #undef BRAHMA_LOGGER_LEVEL_ERROR */
/* #undef BRAHMA_LOGGER_LEVEL_WARN */
/* #undef BRAHMA_LOGGER_LEVEL_INFO */
/* #undef BRAHMA_LOGGER_LEVEL_DEBUG */
/* #undef BRAHMA_LOGGER_LEVEL_TRACE */

// versions
#define BRAHMA_HDF5_VERSION 101405
#define BRAHMA_MPI_VERSION 900001
// MPI implementation name string (OPENMPI, MPICH, CRAYMPICH, MVAPICH, INTELMPI, UNKNOWN)
#define BRAHMA_MPI_IMPL_NAME "CRAYMPICH"


//==========================
// Common macro definitions
//==========================

#define BRAHMA_PATH_DELIM "/"

// #define BRAHMA_NOOP_MACRO do {} while (0)
#define BRAHMA_NOOP_MACRO

// Detect VAR_OPT
// https://stackoverflow.com/questions/48045470/portably-detect-va-opt-support
#if __cplusplus <= 201703 && defined __GNUC__ && !defined __clang__ && \
    !defined __EDG__
#define VA_OPT_SUPPORTED false
#else
#define PP_THIRD_ARG(a, b, c, ...) c
#define VA_OPT_SUPPORTED_I(...) PP_THIRD_ARG(__VA_OPT__(, ), true, false, )
#define VA_OPT_SUPPORTED VA_OPT_SUPPORTED_I(?)
#endif

#if !defined(BRAHMA_HASH_SEED) || (BRAHMA_HASH_SEED <= 0)
#define BRAHMA_SEED 104723u
#endif

#endif /* BRAHMA_CONFIG_H */
