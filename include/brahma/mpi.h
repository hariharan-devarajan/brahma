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
  template <typename C>
  size_t bind(const char *name, uint16_t priority);

  virtual int MPI_Init(int *argc, char ***argv);

  virtual int MPI_Finalize();
};
}  // namespace brahma
GOTCHA_MACRO_TYPEDEF(MPI_Init, int, (int *argc, char ***argv), (argc, argv),
                     brahma::MPI)
GOTCHA_MACRO_TYPEDEF(MPI_Finalize, int, (), (), brahma::MPI)

GOTCHA_MACRO(MPI_Init, int, (int *argc, char ***argv), (argc, argv),
             brahma::MPI)
GOTCHA_MACRO(MPI_Finalize, int, (), (), brahma::MPI)

template <typename C>
size_t brahma::MPI::bind(const char *name, uint16_t priority) {
  GOTCHA_BINDING_MACRO(MPI_Init, MPI);
  GOTCHA_BINDING_MACRO(MPI_Finalize, MPI);
  num_bindings = bindings.size();
  if (num_bindings > 0) {
    char tool_name[64];
    sprintf(tool_name, "%s_stdio", name);
    gotcha_binding_t *raw_bindings = bindings.data();
    gotcha_wrap(raw_bindings, num_bindings, tool_name);
    gotcha_set_priority(tool_name, priority);
  }
  return num_bindings;
}
#endif  // BRAHMA_ENABLE_MPI
#endif  // BRAHMA_MPI_H
