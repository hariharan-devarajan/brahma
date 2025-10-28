# Brahma Docker CI Makefile

DOCKER_IMAGE := brahma-ci
DOCKER_TAG := latest
DOCKERFILE := infrastructure/docker/Dockerfile.ci
BUILD_CONTEXT := .

.PHONY: help build run clean test-all test-mpi test-hdf5 test-full

help: ## Show this help message
	@echo "Brahma Docker CI Commands:"
	@echo ""
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "\033[36m%-15s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST)

build: ## Build the CI Docker image
	docker build -f $(DOCKERFILE) -t $(DOCKER_IMAGE):$(DOCKER_TAG) $(BUILD_CONTEXT)

run: ## Run interactive container with source mounted
	docker run -it --rm -v $(PWD):/workspace $(DOCKER_IMAGE):$(DOCKER_TAG)

clean: ## Remove Docker image and containers
	docker rmi $(DOCKER_IMAGE):$(DOCKER_TAG) || true
	docker container prune -f

# Test targets using docker-compose
test-all: ## Run all test configurations
	docker-compose -f infrastructure/docker/docker-compose.yml up --build --abort-on-container-exit brahma-ci

test-mpi: ## Test MPI-only configuration
	docker-compose -f infrastructure/docker/docker-compose.yml up --build --abort-on-container-exit brahma-test-mpi-only

test-hdf5: ## Test HDF5-only configuration  
	docker-compose -f infrastructure/docker/docker-compose.yml up --build --abort-on-container-exit brahma-test-hdf5-only

test-full: ## Test full MPI+HDF5 configuration
	docker-compose -f infrastructure/docker/docker-compose.yml up --build --abort-on-container-exit brahma-test-full

# Individual build tests
test-basic: build ## Test basic build (no MPI, no HDF5)
	docker run --rm -v $(PWD):/workspace $(DOCKER_IMAGE):$(DOCKER_TAG) \
		/workspace/infrastructure/docker/build.sh

test-mpi-mpich3: build ## Test MPICH 3.x build
	docker run --rm -v $(PWD):/workspace $(DOCKER_IMAGE):$(DOCKER_TAG) \
		/workspace/infrastructure/docker/build.sh --enable-mpi --mpi-impl mpich --mpi-version 3.4.3

test-mpi-mpich4: build ## Test MPICH 4.x build
	docker run --rm -v $(PWD):/workspace $(DOCKER_IMAGE):$(DOCKER_TAG) \
		/workspace/infrastructure/docker/build.sh --enable-mpi --mpi-impl mpich --mpi-version 4.2.3

test-mpi-ompi4: build ## Test OpenMPI 4.x build
	docker run --rm -v $(PWD):/workspace $(DOCKER_IMAGE):$(DOCKER_TAG) \
		/workspace/infrastructure/docker/build.sh --enable-mpi --mpi-impl openmpi --mpi-version 4.1.6

test-mpi-ompi5: build ## Test OpenMPI 5.x build
	docker run --rm -v $(PWD):/workspace $(DOCKER_IMAGE):$(DOCKER_TAG) \
		/workspace/infrastructure/docker/build.sh --enable-mpi --mpi-impl openmpi --mpi-version 5.0.6

test-hdf5-18: build ## Test HDF5 1.8.x build
	docker run --rm -v $(PWD):/workspace $(DOCKER_IMAGE):$(DOCKER_TAG) \
		/workspace/infrastructure/docker/build.sh --enable-hdf5 --hdf5-version 1.8.23

test-hdf5-110: build ## Test HDF5 1.10.x build
	docker run --rm -v $(PWD):/workspace $(DOCKER_IMAGE):$(DOCKER_TAG) \
		/workspace/infrastructure/docker/build.sh --enable-hdf5 --hdf5-version 1.10.11

test-hdf5-112: build ## Test HDF5 1.12.x build
	docker run --rm -v $(PWD):/workspace $(DOCKER_IMAGE):$(DOCKER_TAG) \
		/workspace/infrastructure/docker/build.sh --enable-hdf5 --hdf5-version 1.12.3

test-hdf5-114: build ## Test HDF5 1.14.x build
	docker run --rm -v $(PWD):/workspace $(DOCKER_IMAGE):$(DOCKER_TAG) \
		/workspace/infrastructure/docker/build.sh --enable-hdf5 --hdf5-version 1.14.5

test-matrix: build ## Run complete test matrix (takes a long time!)
	@echo "Running complete test matrix..."
	$(MAKE) test-basic
	$(MAKE) test-mpi-mpich3
	$(MAKE) test-mpi-mpich4
	$(MAKE) test-mpi-ompi4
	$(MAKE) test-hdf5-18
	$(MAKE) test-hdf5-110
	$(MAKE) test-hdf5-112
	$(MAKE) test-hdf5-114
	@echo "Full test matrix completed!"

# Docker image info
info: ## Show Docker image information
	@echo "Docker Image: $(DOCKER_IMAGE):$(DOCKER_TAG)"
	@echo "Dockerfile: $(DOCKERFILE)"
	@echo "Build Context: $(BUILD_CONTEXT)"
	@docker images $(DOCKER_IMAGE):$(DOCKER_TAG) || echo "Image not built yet"

# Development helpers
shell: build ## Open shell in container
	docker run -it --rm -v $(PWD):/workspace $(DOCKER_IMAGE):$(DOCKER_TAG) /bin/bash

packages: build ## Show installed packages in container
	docker run --rm $(DOCKER_IMAGE):$(DOCKER_TAG) /home/spack/show_packages.sh