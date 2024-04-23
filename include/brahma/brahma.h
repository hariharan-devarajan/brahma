//
// Created by hariharan on 8/8/22.
//

#ifndef BRAHMA_BRAHMA_H
#define BRAHMA_BRAHMA_H
#ifdef BRAHMA_ENABLE_MPI
#include <brahma/interface/mpiio.h>
#endif
#include <brahma/interface/posix.h>
#include <brahma/interface/stdio.h>

#include <cassert>

extern void brahma_gotcha_wrap(const char *name, uint16_t priority);

#endif  // BRAHMA_BRAHMA_H
