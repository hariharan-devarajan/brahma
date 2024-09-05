//
// Created by hariharan on 8/16/22.
//
#include <brahma/interceptor.h>

namespace brahma {
gotcha_binding_t* bindings = nullptr;
size_t total_apis = 0;
}  // namespace brahma

extern int brahma_bind_functions() {
  BRAHMA_LOGGER_INIT();
  if (brahma::bindings == nullptr) {
#if defined(BRAHMA_ENABLE_HDF5) && defined(BRAHMA_ENABLE_MPI)
    brahma::total_apis = count_posix() + count_stdio() + count_mpi() +
                         count_mpiio() + count_hdf5();
#elif defined(BRAHMA_ENABLE_HDF5)
    brahma::total_apis = count_posix() + count_stdio() + count_hdf5();
#elif defined(BRAHMA_ENABLE_MPI)
    brahma::total_apis =
        count_posix() + count_stdio() + count_mpi() + count_mpiio();
#else
    brahma::total_apis = count_posix() + count_stdio();
#endif
    brahma::bindings = static_cast<gotcha_binding_t*>(
        calloc(brahma::total_apis, sizeof(gotcha_binding_t)));
    size_t current_index = 0;
    update_posix(brahma::bindings, current_index);
    update_stdio(brahma::bindings, current_index);
#ifdef BRAHMA_ENABLE_MPI
    update_mpiio(brahma::bindings, current_index);
    update_mpi(brahma::bindings, current_index);
#endif
#ifdef BRAHMA_ENABLE_HDF5
    update_hdf5(brahma::bindings, current_index);
#endif
    if (current_index != brahma::total_apis) {
      BRAHMA_LOG_ERROR(
          "brahma_bind_functions do not match total apis %ld of %ld",
          current_index, brahma::total_apis);
      return -1;
    }
  }
  return 0;
}

extern int brahma_get_binding(gotcha_binding_t*& bindings_i,
                              size_t& binding_count) {
  bindings_i = brahma::bindings;
  binding_count = brahma::total_apis;
  return 0;
}

extern int brahma_free_bindings() {
  free(brahma::bindings);
  return 0;
}