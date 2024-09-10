//
// Created by haridev on 9/6/22.
//
#include <brahma/mpi.h>

#include <brahma/brahma_config.hpp>
/* Internal Headers */
#include <brahma/interceptor.h>
#include <brahma/interface/interface.h>
/* External Headers */

#ifdef BRAHMA_ENABLE_MPI


int update_mpi(gotcha_binding_t *&bindings, size_t &binding_index) {
  
  return 0;
}


namespace brahma {
std::shared_ptr<MPI> MPI::my_instance = nullptr;
int MPI::MPI_Init(int *argc, char ***argv) {
  BRAHMA_UNWRAPPED_FUNC(MPI_Init, int, (argc, argv));
  return result;
}
int MPI::MPI_Finalize() {
  BRAHMA_UNWRAPPED_FUNC(MPI_Finalize, int, ());
  return result;
}
}  // namespace brahma
#endif  // BRAHMA_ENABLE_MPI