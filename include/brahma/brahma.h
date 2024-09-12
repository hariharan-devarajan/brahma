//
// Created by hariharan on 8/8/22.
//

#ifndef BRAHMA_BRAHMA_H
#define BRAHMA_BRAHMA_H

#include <brahma/brahma_config.hpp>
/* Internal Headers */
#ifdef BRAHMA_ENABLE_HDF5
#include <brahma/interface/hdf5.h>
#endif
#ifdef BRAHMA_ENABLE_MPI
#include <brahma/interface/mpiio.h>
#endif
#include <brahma/interface/posix.h>
#include <brahma/interface/stdio.h>
/* External Headers */
#include <cassert>

#endif  // BRAHMA_BRAHMA_H
