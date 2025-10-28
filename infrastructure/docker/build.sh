#!/bin/bash

# Brahma CI Build Script
# This script replicates the GitHub Actions CI workflow in the Docker environment

set -e

# Default values
BUILD_TYPE=${BUILD_TYPE:-Debug}
ENABLE_MPI=${ENABLE_MPI:-OFF}
ENABLE_HDF5=${ENABLE_HDF5:-OFF}
MPI_IMPL=${MPI_IMPL:-openmpi}
MPI_VERSION=${MPI_VERSION:-4.1.6}
HDF5_VERSION=${HDF5_VERSION:-1.14.5}
JOBS=${JOBS:-$(nproc)}

# Function to print usage
usage() {
    echo "Usage: $0 [OPTIONS]"
    echo "Options:"
    echo "  --mpi-impl <openmpi|mpich>     MPI implementation (default: openmpi)"
    echo "  --mpi-version <version>        MPI version (default: 4.1.6)"
    echo "  --hdf5-version <version>       HDF5 version (default: 1.14.5)"
    echo "  --enable-mpi                   Enable MPI support"
    echo "  --enable-hdf5                  Enable HDF5 support"
    echo "  --build-type <Debug|Release>   Build type (default: Debug)"
    echo "  --jobs <N>                     Number of parallel jobs (default: nproc)"
    echo "  --help                         Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0 --enable-mpi --mpi-impl mpich --mpi-version 3.4.3"
    echo "  $0 --enable-hdf5 --hdf5-version 1.12.3"
    echo "  $0 --enable-mpi --enable-hdf5 --mpi-impl openmpi --hdf5-version 1.14.5"
}

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --enable-mpi)
            ENABLE_MPI=ON
            shift
            ;;
        --enable-hdf5)
            ENABLE_HDF5=ON
            shift
            ;;
        --mpi-impl)
            MPI_IMPL="$2"
            shift 2
            ;;
        --mpi-version)
            MPI_VERSION="$2"
            shift 2
            ;;
        --hdf5-version)
            HDF5_VERSION="$2"
            shift 2
            ;;
        --build-type)
            BUILD_TYPE="$2"
            shift 2
            ;;
        --jobs)
            JOBS="$2"
            shift 2
            ;;
        --help)
            usage
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            usage
            exit 1
            ;;
    esac
done

echo "=== Brahma CI Build Configuration ==="
echo "Build Type: $BUILD_TYPE"
echo "Enable MPI: $ENABLE_MPI"
echo "Enable HDF5: $ENABLE_HDF5"
if [[ "$ENABLE_MPI" == "ON" ]]; then
    echo "MPI Implementation: $MPI_IMPL"
    echo "MPI Version: $MPI_VERSION"
fi
if [[ "$ENABLE_HDF5" == "ON" ]]; then
    echo "HDF5 Version: $HDF5_VERSION"
fi
echo "Parallel Jobs: $JOBS"
echo "======================================"

# Source spack environment
source $SPACK_ROOT/share/spack/setup-env.sh

# Load appropriate environment based on configuration
if [[ "$ENABLE_MPI" == "ON" && "$ENABLE_HDF5" == "ON" ]]; then
    echo "Loading MPI + HDF5 environment..."
    source /home/spack/load_env.sh $MPI_IMPL $MPI_VERSION $HDF5_VERSION
elif [[ "$ENABLE_MPI" == "ON" ]]; then
    echo "Loading MPI-only environment..."
    source /home/spack/load_env.sh $MPI_IMPL $MPI_VERSION
elif [[ "$ENABLE_HDF5" == "ON" ]]; then
    echo "Loading HDF5-only environment..."
    spack load gcc@12.4.0
    spack load hdf5@"$HDF5_VERSION"
    CC=$(which gcc)
    CXX=$(which g++)
    export CC CXX
else
    echo "Loading basic environment..."
    spack load gcc@12.4.0
    CC=$(which gcc)
    CXX=$(which g++)
    export CC CXX
fi

# Verify environment
echo "=== Environment Verification ==="
echo "CC: $CC"
echo "CXX: $CXX"
if [[ "$ENABLE_MPI" == "ON" ]]; then
    echo "MPI CC: $(which mpicc)"
    echo "MPI CXX: $(which mpic++)"
fi
echo "================================="

# Clean build directory
echo "Cleaning build directory..."
rm -rf build
mkdir -p build

# Install Python requirements for interface generation
echo "Installing Python requirements..."
python3 -m pip install -r tools/requirements.txt

# Prepare CMake arguments
CMAKE_ARGS=(
    "-DCMAKE_BUILD_TYPE=$BUILD_TYPE"
    -DBRAHMA_ENABLE_TESTING=ON
)

# Add MPI configuration
if [[ "$ENABLE_MPI" == "ON" ]]; then
    CMAKE_ARGS+=(
        -DBRAHMA_BUILD_WITH_MPI=ON
    )
    if [[ -n "$MPI_DIR" ]]; then
        CMAKE_ARGS+=("-DMPI_ROOT=$MPI_DIR")
    fi
fi

# Add HDF5 configuration
if [[ "$ENABLE_HDF5" == "ON" ]]; then
    CMAKE_ARGS+=(
        -DBRAHMA_BUILD_WITH_HDF5=ON
    )
    HDF5_ROOT=$(spack location -i hdf5)
    if [[ -n "$HDF5_ROOT" ]]; then
        CMAKE_ARGS+=("-DHDF5_ROOT=$HDF5_ROOT")
    fi
fi

echo "=== CMake Configuration ==="
echo "Arguments: ${CMAKE_ARGS[*]}"
echo "============================"

# Step 1: Generate interfaces (if needed)
if [[ "$ENABLE_MPI" == "ON" || "$ENABLE_HDF5" == "ON" ]]; then
    echo "=== Generating Interfaces ==="
    CMAKE_ARGS_GEN=("${CMAKE_ARGS[@]}")
    CMAKE_ARGS_GEN+=(
        -DBRAHMA_BUILD_DEPENDENCIES=OFF
        -DBRAHMA_GENERATE_INTERFACES=ON
    )
    cmake -Bbuild "${CMAKE_ARGS_GEN[@]}"
    make -C build -j$JOBS
fi

# Step 2: Build dependencies
echo "=== Building Dependencies ==="
CMAKE_ARGS_DEPS=("${CMAKE_ARGS[@]}")
CMAKE_ARGS_DEPS+=(
    -DBRAHMA_BUILD_DEPENDENCIES=ON
    -DBRAHMA_GENERATE_INTERFACES=OFF
)
cmake -Bbuild "${CMAKE_ARGS_DEPS[@]}"
make -C build -j$JOBS

# Step 3: Build main project
echo "=== Building Main Project ==="
CMAKE_ARGS_BUILD=("${CMAKE_ARGS[@]}")
CMAKE_ARGS_BUILD+=(
    -DBRAHMA_BUILD_DEPENDENCIES=OFF
    -DBRAHMA_GENERATE_INTERFACES=OFF
)
cmake -Bbuild "${CMAKE_ARGS_BUILD[@]}"
make -C build -j$JOBS

# Step 4: Run tests
echo "=== Running Tests ==="
ctest --test-dir build -VV

echo "=== Build Complete ==="
echo "Build succeeded with configuration:"
echo "  MPI: $ENABLE_MPI ($MPI_IMPL $MPI_VERSION)"
echo "  HDF5: $ENABLE_HDF5 ($HDF5_VERSION)"
echo "  Build Type: $BUILD_TYPE"