#!/bin/bash
# Runs ON the allocated compute node (invoked via
#   flux proxy <jobid> flux run -N 1 bash .gitlab/ci/build-test-docs.sh)
# and executes the CI inside podman containers using the same images as the
# GitHub Actions CI (hdevarajan92/brahma-ci for build/test, python:3.11 for
# docs) so GitLab CI mimics GitHub CI as closely as possible.
set -ex

# Rootless podman needs node-local storage (overlayfs does not work on NFS
# homes/workspaces). Keep image store + runroot in /var/tmp on the node.
PODMAN_STORE=/var/tmp/$USER/podman-root
PODMAN_RUNROOT=/var/tmp/$USER/podman-run
mkdir -p "$PODMAN_STORE" "$PODMAN_RUNROOT"
PODMAN="podman --root $PODMAN_STORE --runroot $PODMAN_RUNROOT"

# The GitHub CI ran a 4-way spack matrix inside this image:
#   hdf5@1.8.23  / mpich@3.4.3
#   hdf5@1.10.11 / openmpi@4.1.6
#   hdf5@1.12.3  / mpich@4.2.3
#   hdf5@1.14.5  / openmpi@5.0.6
# We keep ONE combo here so the pipeline fits in the shared allocation's
# walltime; the other three can be enabled by looping over them below (or by
# adding a GitLab `parallel: matrix:` with its own allocation).
HDF5=${HDF5:-hdf5@1.14.5}
MPI=${MPI:-openmpi@5.0.6}

$PODMAN run --rm -v "$PWD:/ws" -w /ws \
  -e HDF5="$HDF5" -e MPI="$MPI" \
  docker.io/hdevarajan92/brahma-ci:latest bash -ec '
  # APT::Sandbox::User=root: rootless podman has no mapped _apt uid, so apts
  # privilege drop fails with "setgroups (22: Invalid argument)".
  # (kept here for any extra package needed by the build)
  source .github/workflows/scripts/load_env.sh "$HDF5" "$MPI"
  mkdir -p build
  cmake -Bbuild \
    -DCMAKE_BUILD_TYPE=Debug \
    -DBRAHMA_ENABLE_TESTING=ON \
    -DBRAHMA_GENERATE_INTERFACES=OFF \
    -DBRAHMA_BUILD_WITH_HDF5=ON \
    -DBRAHMA_BUILD_WITH_MPI=ON \
    -DHDF5_ROOT="$HDF5_DIR" \
    -DMPI_ROOT="$MPI_DIR" \
    -DBRAHMA_BUILD_DEPENDENCIES=ON
  make -C build -j "$(nproc)"
  ctest --test-dir build -VV
'

# Docs in the same image the pages job used.
$PODMAN run --rm -v "$PWD:/ws" -w /ws docker.io/library/python:3.11 bash -ec '
  pip install -r docs/requirements.txt
  sphinx-build -b html docs public
'
