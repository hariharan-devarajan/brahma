# Brahma CI Docker Image

This Docker image provides a complete CI environment for building and testing Brahma with various combinations of MPI implementations and HDF5 versions.

## Features

- **Base OS**: Ubuntu 24.04
- **Compiler**: GCC 12.4.0
- **MPI Implementations**:
  - OpenMPI 4.1.6, 5.0.6
  - MPICH 3.4.3, 4.2.3
- **HDF5 Versions**: 1.8.23, 1.10.11, 1.12.3, 1.14.5
  - Available both with and without MPI support
- **Package Manager**: Spack (latest release)
- **System Dependencies**: All packages from the CI workflow

## Building the Image

```bash
# From the brahma root directory
docker build -f infrastructure/docker/Dockerfile.ci -t brahma-ci:latest .
```

## Multi-Architecture Build and Push

```bash
# Build and push for multiple architectures (requires Docker Buildx)
docker buildx create --name multiarch --use
docker buildx build \
   --platform linux/amd64,linux/arm64 \
   -f infrastructure/docker/Dockerfile.ci \
   --push \
   -t brahma-ci:latest \
   .

# Push to a specific registry
docker buildx build \
   --platform linux/amd64,linux/arm64 \
   -f infrastructure/docker/Dockerfile.ci \
   --push \
   -t hdevarajan92/brahma-ci:latest \
   .
```

## Using the Image

### Basic Usage

```bash
# Run interactive container
docker run -it --rm brahma-ci:latest

# Mount your source code
docker run -it --rm -v $PWD:/workspace brahma-ci:latest
source .github/workflows/scripts/load_env.sh "hdf5@1.14.5" "openmpi@5.0.6"

```

### Environment Loading

The image provides a helper script to load different MPI and HDF5 combinations:

```bash
# Load default environment (OpenMPI 4.1.6 + HDF5 1.14.5)
source /home/spack/load_env.sh

# Load specific MPI implementation and version
source /home/spack/load_env.sh openmpi 4.1.6

# Load specific MPI and HDF5 combination
source /home/spack/load_env.sh mpich 3.4.3 1.12.3

# Available combinations:
# MPI: openmpi (4.1.6, 5.0.6), mpich (3.4.3, 4.2.3)
# HDF5: 1.8.23, 1.10.11, 1.12.3, 1.14.5
```

### Viewing Available Packages

```bash
# Show all installed packages
/home/spack/show_packages.sh

# Or use the alias
show-packages
```

### Building Brahma

Once you've loaded the desired environment:

```bash
# Navigate to brahma source
cd /workspace

# Install Python requirements for interface generation
python3 -m pip install -r tools/requirements.txt

# Configure build (example with MPI and HDF5)
cmake -Bbuild \
  -DBRAHMA_BUILD_DEPENDENCIES=OFF \
  -DBRAHMA_ENABLE_TESTING=ON \
  -DBRAHMA_BUILD_WITH_MPI=ON \
  -DBRAHMA_BUILD_WITH_HDF5=ON

# Build
make -C build -j$(nproc)

# Run tests
ctest --test-dir build -VV
```

## Testing Matrix

The image supports all combinations from the CI matrix:

1. **No MPI, No HDF5**: Basic build without external libraries
2. **MPI Only**: 
   - MPICH 3.4.3, 4.2.3
   - OpenMPI 4.1.6, 5.0.6
3. **HDF5 Only**: 
   - Versions 1.8.23, 1.10.11, 1.12.3, 1.14.5
4. **MPI + HDF5**: All combinations of the above

## Environment Variables

The following variables are automatically set when loading environments:

- `CC`: MPI C compiler (mpicc)
- `CXX`: MPI C++ compiler (mpic++)
- `FC`: MPI Fortran compiler (mpifort)
- `SPACK_ROOT`: Path to Spack installation

## Useful Commands

```bash
# Show spack status
spack find

# Load specific packages
spack load gcc@12.4.0
spack load openmpi@4.1.6
spack load hdf5@1.14.5^openmpi@4.1.6

# Unload all packages
spack unload --all

# Check loaded packages
spack find --loaded
```

## Troubleshooting

1. **Environment not loaded**: Make sure to source the spack environment:
   ```bash
   source $SPACK_ROOT/share/spack/setup-env.sh
   ```

2. **Missing compilers**: Verify GCC 12 is loaded:
   ```bash
   spack load gcc@12.4.0
   ```

3. **Package conflicts**: Unload all packages and reload:
   ```bash
   spack unload --all
   source /home/spack/load_env.sh <mpi> <version> <hdf5>
   ```

## Size Optimization

The image includes spack cache cleanup to reduce size. If you need to install additional packages, you may need to rebuild some dependencies.