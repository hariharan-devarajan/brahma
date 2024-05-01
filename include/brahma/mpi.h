//
// Created by haridev on 9/6/22.
//

#ifndef BRAHMA_MPI_H
#define BRAHMA_MPI_H

#include <brahma/brahma_config.hpp>
/* Internal Headers */
#include <brahma/interceptor.h>
#include <brahma/interface/interface.h>
#include <brahma/logging.h>
/* External Headers */

#ifdef BRAHMA_ENABLE_MPI

#include <mpi.h>

#include <stdexcept>
namespace brahma {
class MPI : public brahma::Interface {
 private:
  static std::shared_ptr<MPI> my_instance;

 public:
  MPI() : Interface() {}
  virtual ~MPI(){};
  static std::shared_ptr<MPI> get_instance() {
    if (my_instance == nullptr) {
      BRAHMA_LOG_INFO("MPI class not intercepted but used", "");
      my_instance = std::make_shared<MPI>();
    }
    return my_instance;
  }

  static int set_instance(std::shared_ptr<MPI> instance_i) {
    if (instance_i != nullptr) {
      my_instance = instance_i;
      return 0;
    } else {
      BRAHMA_LOG_ERROR("%s instance_i is not set", "MPI");
      throw std::runtime_error("instance_i is not set");
    }
  }

  virtual int MPI_Init(int *argc, char ***argv);

  virtual int MPI_Finalize();
};
}  // namespace brahma
GOTCHA_MACRO_TYPEDEF(MPI_Init, int, (int *argc, char ***argv), (argc, argv),
                     brahma::MPI)
GOTCHA_MACRO_TYPEDEF(MPI_Finalize, int, (), (), brahma::MPI)
#endif  // BRAHMA_ENABLE_MPI
#endif  // BRAHMA_MPI_H
