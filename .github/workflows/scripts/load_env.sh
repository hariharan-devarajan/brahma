#!/bin/bash

# Check if required packages are provided as arguments
if [ $# -lt 2 ]; then
    echo "Error: Required packages not provided"
    echo "Usage: $0 <HDF5_PACKAGE> <MPI_PACKAGE>"
    exit 1
fi

HDF5_PACKAGE=$1
MPI_PACKAGE=$2

echo "[$(date '+%Y-%m-%d %H:%M:%S')] Starting environment setup..."

echo "[$(date '+%Y-%m-%d %H:%M:%S')] Sourcing spack setup..."
source /home/spack/spack/share/spack/setup-env.sh

echo "[$(date '+%Y-%m-%d %H:%M:%S')] Loading spack packages..."
spack load ${HDF5_PACKAGE}
spack load ${MPI_PACKAGE}
spack load cmake

echo "[$(date '+%Y-%m-%d %H:%M:%S')] Setting environment variables..."
export HDF5_DIR=$(spack location -i ${HDF5_PACKAGE})
export MPI_DIR=$(spack location -i ${MPI_PACKAGE})
export CC=$(which mpicc)
export CXX=$(which mpic++)

echo "[$(date '+%Y-%m-%d %H:%M:%S')] Environment variables set:"
echo "  HDF5_DIR=$HDF5_DIR"
echo "  MPI_DIR=$MPI_DIR"
echo "  CC=$CC"
echo "  CXX=$CXX"

echo "[$(date '+%Y-%m-%d %H:%M:%S')] Checking loaded packages..."
spack find --loaded

echo "[$(date '+%Y-%m-%d %H:%M:%S')] Environment setup complete."