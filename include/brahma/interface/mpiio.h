//
// Created by hariharan on 8/8/22.
//

#ifndef BRAHMA_MPIIO_H
#define BRAHMA_MPIIO_H
#include <brahma/brahma_config.hpp>
#ifdef BRAHMA_ENABLE_MPI
/* Internal header */
#include <brahma/interceptor.h>
#include <brahma/interface/interface.h>
/* Headers */
#include <mpi.h>

namespace brahma {
class MPIIO : public Interface {
 private:
  static std::shared_ptr<MPIIO> my_instance;

 public:
  MPIIO() : Interface() {}
  virtual ~MPIIO(){};
  static std::shared_ptr<MPIIO> get_instance();

  template <typename C>
  size_t bind(const char *name, uint16_t priority);

  static int set_instance(std::shared_ptr<MPIIO> instance_i);

  virtual int MPI_File_close(MPI_File *fh);

  virtual int MPI_File_set_size(MPI_File fh, MPI_Offset size);

  virtual int MPI_File_iread_at(MPI_File fh, MPI_Offset offset, void *buf,
                                int count, MPI_Datatype datatype,
                                MPI_Request *request);

  virtual int MPI_File_iread(MPI_File fh, void *buf, int count,
                             MPI_Datatype datatype, MPI_Request *request);

  virtual int MPI_File_iread_shared(MPI_File fh, void *buf, int count,
                                    MPI_Datatype datatype,
                                    MPI_Request *request);

  virtual int MPI_File_iwrite_at(MPI_File fh, MPI_Offset offset,
                                 const void *buf, int count,
                                 MPI_Datatype datatype, MPI_Request *request);

  virtual int MPI_File_iwrite(MPI_File fh, const void *buf, int count,
                              MPI_Datatype datatype, MPI_Request *request);

  virtual int MPI_File_iwrite_shared(MPI_File fh, const void *buf, int count,
                                     MPI_Datatype datatype,
                                     MPI_Request *request);

  virtual int MPI_File_open(MPI_Comm comm, const char *filename, int amode,
                            MPI_Info info, MPI_File *fh);

  virtual int MPI_File_read_all_begin(MPI_File fh, void *buf, int count,
                                      MPI_Datatype datatype);

  virtual int MPI_File_read_all(MPI_File fh, void *buf, int count,
                                MPI_Datatype datatype, MPI_Status *status);

  virtual int MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf,
                                   int count, MPI_Datatype datatype,
                                   MPI_Status *status);

  virtual int MPI_File_read_at_all_begin(MPI_File fh, MPI_Offset offset,
                                         void *buf, int count,
                                         MPI_Datatype datatype);

  virtual int MPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf,
                               int count, MPI_Datatype datatype,
                               MPI_Status *status);

  virtual int MPI_File_read(MPI_File fh, void *buf, int count,
                            MPI_Datatype datatype, MPI_Status *status);

  virtual int MPI_File_read_ordered_begin(MPI_File fh, void *buf, int count,
                                          MPI_Datatype datatype);

  virtual int MPI_File_read_ordered(MPI_File fh, void *buf, int count,
                                    MPI_Datatype datatype, MPI_Status *status);

  virtual int MPI_File_read_shared(MPI_File fh, void *buf, int count,
                                   MPI_Datatype datatype, MPI_Status *status);

  virtual int MPI_File_sync(MPI_File fh);

  virtual int MPI_File_write_all_begin(MPI_File fh, const void *buf, int count,
                                       MPI_Datatype datatype);

  virtual int MPI_File_write_all(MPI_File fh, const void *buf, int count,
                                 MPI_Datatype datatype, MPI_Status *status);

  virtual int MPI_File_write_at_all_begin(MPI_File fh, MPI_Offset offset,
                                          const void *buf, int count,
                                          MPI_Datatype datatype);

  virtual int MPI_File_write_at_all(MPI_File fh, MPI_Offset offset,
                                    const void *buf, int count,
                                    MPI_Datatype datatype, MPI_Status *status);

  virtual int MPI_File_write_at(MPI_File fh, MPI_Offset offset, const void *buf,
                                int count, MPI_Datatype datatype,
                                MPI_Status *status);

  virtual int MPI_File_write(MPI_File fh, const void *buf, int count,
                             MPI_Datatype datatype, MPI_Status *status);

  virtual int MPI_File_write_ordered_begin(MPI_File fh, const void *buf,
                                           int count, MPI_Datatype datatype);

  virtual int MPI_File_write_ordered(MPI_File fh, const void *buf, int count,
                                     MPI_Datatype datatype, MPI_Status *status);

  virtual int MPI_File_write_shared(MPI_File fh, const void *buf, int count,
                                    MPI_Datatype datatype, MPI_Status *status);
  virtual int MPI_File_delete(const char *filename, MPI_Info info);
};

}  // namespace brahma

GOTCHA_MACRO_TYPEDEF(MPI_File_close, int, (MPI_File * fh), (fh), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_set_size, int, (MPI_File fh, MPI_Offset size),
                     (fh, size), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_iread_at, int,
                     (MPI_File fh, MPI_Offset offset, void *buf, int count,
                      MPI_Datatype datatype, MPI_Request *request),
                     (fh, offset, buf, count, datatype, request), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_iread, int,
                     (MPI_File fh, void *buf, int count, MPI_Datatype datatype,
                      MPI_Request *request),
                     (fh, buf, count, datatype, request), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_iread_shared, int,
                     (MPI_File fh, void *buf, int count, MPI_Datatype datatype,
                      MPI_Request *request),
                     (fh, buf, count, datatype, request), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_iwrite_at, int,
                     (MPI_File fh, MPI_Offset offset, const void *buf,
                      int count, MPI_Datatype datatype, MPI_Request *request),
                     (fh, offset, buf, count, datatype, request), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_iwrite, int,
                     (MPI_File fh, const void *buf, int count,
                      MPI_Datatype datatype, MPI_Request *request),
                     (fh, buf, count, datatype, request), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_iwrite_shared, int,
                     (MPI_File fh, const void *buf, int count,
                      MPI_Datatype datatype, MPI_Request *request),
                     (fh, buf, count, datatype, request), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_open, int,
                     (MPI_Comm comm, const char *filename, int amode,
                      MPI_Info info, MPI_File *fh),
                     (comm, filename, amode, info, fh), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_read_all_begin, int,
                     (MPI_File fh, void *buf, int count, MPI_Datatype datatype),
                     (fh, buf, count, datatype), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_read_all, int,
                     (MPI_File fh, void *buf, int count, MPI_Datatype datatype,
                      MPI_Status *status),
                     (fh, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_read_at_all, int,
                     (MPI_File fh, MPI_Offset offset, void *buf, int count,
                      MPI_Datatype datatype, MPI_Status *status),
                     (fh, offset, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_read_at_all_begin, int,
                     (MPI_File fh, MPI_Offset offset, void *buf, int count,
                      MPI_Datatype datatype),
                     (fh, offset, buf, count, datatype), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_read_at, int,
                     (MPI_File fh, MPI_Offset offset, void *buf, int count,
                      MPI_Datatype datatype, MPI_Status *status),
                     (fh, offset, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_read, int,
                     (MPI_File fh, void *buf, int count, MPI_Datatype datatype,
                      MPI_Status *status),
                     (fh, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_read_ordered_begin, int,
                     (MPI_File fh, void *buf, int count, MPI_Datatype datatype),
                     (fh, buf, count, datatype), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_read_ordered, int,
                     (MPI_File fh, void *buf, int count, MPI_Datatype datatype,
                      MPI_Status *status),
                     (fh, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_read_shared, int,
                     (MPI_File fh, void *buf, int count, MPI_Datatype datatype,
                      MPI_Status *status),
                     (fh, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_sync, int, (MPI_File fh), (fh), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_write_all_begin, int,
                     (MPI_File fh, const void *buf, int count,
                      MPI_Datatype datatype),
                     (fh, buf, count, datatype), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_write_all, int,
                     (MPI_File fh, const void *buf, int count,
                      MPI_Datatype datatype, MPI_Status *status),
                     (fh, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_write_at_all_begin, int,
                     (MPI_File fh, MPI_Offset offset, const void *buf,
                      int count, MPI_Datatype datatype),
                     (fh, offset, buf, count, datatype), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_write_at_all, int,
                     (MPI_File fh, MPI_Offset offset, const void *buf,
                      int count, MPI_Datatype datatype, MPI_Status *status),
                     (fh, offset, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_write_at, int,
                     (MPI_File fh, MPI_Offset offset, const void *buf,
                      int count, MPI_Datatype datatype, MPI_Status *status),
                     (fh, offset, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_write, int,
                     (MPI_File fh, const void *buf, int count,
                      MPI_Datatype datatype, MPI_Status *status),
                     (fh, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_write_ordered_begin, int,
                     (MPI_File fh, const void *buf, int count,
                      MPI_Datatype datatype),
                     (fh, buf, count, datatype), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_write_ordered, int,
                     (MPI_File fh, const void *buf, int count,
                      MPI_Datatype datatype, MPI_Status *status),
                     (fh, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_write_shared, int,
                     (MPI_File fh, const void *buf, int count,
                      MPI_Datatype datatype, MPI_Status *status),
                     (fh, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO_TYPEDEF(MPI_File_delete, int,
                     (const char *filename, MPI_Info info), (filename, info),
                     brahma::MPIIO)

GOTCHA_MACRO(MPI_File_close, int, (MPI_File * fh), (fh), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_set_size, int, (MPI_File fh, MPI_Offset size), (fh, size),
             brahma::MPIIO)

GOTCHA_MACRO(MPI_File_iread_at, int,
             (MPI_File fh, MPI_Offset offset, void *buf, int count,
              MPI_Datatype datatype, MPI_Request *request),
             (fh, offset, buf, count, datatype, request), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_iread, int,
             (MPI_File fh, void *buf, int count, MPI_Datatype datatype,
              MPI_Request *request),
             (fh, buf, count, datatype, request), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_iread_shared, int,
             (MPI_File fh, void *buf, int count, MPI_Datatype datatype,
              MPI_Request *request),
             (fh, buf, count, datatype, request), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_iwrite_at, int,
             (MPI_File fh, MPI_Offset offset, const void *buf, int count,
              MPI_Datatype datatype, MPI_Request *request),
             (fh, offset, buf, count, datatype, request), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_iwrite, int,
             (MPI_File fh, const void *buf, int count, MPI_Datatype datatype,
              MPI_Request *request),
             (fh, buf, count, datatype, request), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_iwrite_shared, int,
             (MPI_File fh, const void *buf, int count, MPI_Datatype datatype,
              MPI_Request *request),
             (fh, buf, count, datatype, request), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_open, int,
             (MPI_Comm comm, const char *filename, int amode, MPI_Info info,
              MPI_File *fh),
             (comm, filename, amode, info, fh), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_read_all_begin, int,
             (MPI_File fh, void *buf, int count, MPI_Datatype datatype),
             (fh, buf, count, datatype), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_read_all, int,
             (MPI_File fh, void *buf, int count, MPI_Datatype datatype,
              MPI_Status *status),
             (fh, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_read_at_all, int,
             (MPI_File fh, MPI_Offset offset, void *buf, int count,
              MPI_Datatype datatype, MPI_Status *status),
             (fh, offset, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_read_at_all_begin, int,
             (MPI_File fh, MPI_Offset offset, void *buf, int count,
              MPI_Datatype datatype),
             (fh, offset, buf, count, datatype), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_read_at, int,
             (MPI_File fh, MPI_Offset offset, void *buf, int count,
              MPI_Datatype datatype, MPI_Status *status),
             (fh, offset, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_read, int,
             (MPI_File fh, void *buf, int count, MPI_Datatype datatype,
              MPI_Status *status),
             (fh, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_read_ordered_begin, int,
             (MPI_File fh, void *buf, int count, MPI_Datatype datatype),
             (fh, buf, count, datatype), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_read_ordered, int,
             (MPI_File fh, void *buf, int count, MPI_Datatype datatype,
              MPI_Status *status),
             (fh, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_read_shared, int,
             (MPI_File fh, void *buf, int count, MPI_Datatype datatype,
              MPI_Status *status),
             (fh, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_sync, int, (MPI_File fh), (fh), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_write_all_begin, int,
             (MPI_File fh, const void *buf, int count, MPI_Datatype datatype),
             (fh, buf, count, datatype), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_write_all, int,
             (MPI_File fh, const void *buf, int count, MPI_Datatype datatype,
              MPI_Status *status),
             (fh, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_write_at_all_begin, int,
             (MPI_File fh, MPI_Offset offset, const void *buf, int count,
              MPI_Datatype datatype),
             (fh, offset, buf, count, datatype), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_write_at_all, int,
             (MPI_File fh, MPI_Offset offset, const void *buf, int count,
              MPI_Datatype datatype, MPI_Status *status),
             (fh, offset, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_write_at, int,
             (MPI_File fh, MPI_Offset offset, const void *buf, int count,
              MPI_Datatype datatype, MPI_Status *status),
             (fh, offset, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_write, int,
             (MPI_File fh, const void *buf, int count, MPI_Datatype datatype,
              MPI_Status *status),
             (fh, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_write_ordered_begin, int,
             (MPI_File fh, const void *buf, int count, MPI_Datatype datatype),
             (fh, buf, count, datatype), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_write_ordered, int,
             (MPI_File fh, const void *buf, int count, MPI_Datatype datatype,
              MPI_Status *status),
             (fh, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_write_shared, int,
             (MPI_File fh, const void *buf, int count, MPI_Datatype datatype,
              MPI_Status *status),
             (fh, buf, count, datatype, status), brahma::MPIIO)

GOTCHA_MACRO(MPI_File_delete, int, (const char *filename, MPI_Info info),
             (filename, info), brahma::MPIIO)

template <typename C>
size_t brahma::MPIIO::bind(const char *name, uint16_t priority) {
  GOTCHA_BINDING_MACRO(MPI_File_close, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_set_size, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_iread_at, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_iread, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_iread_shared, MPIIO);

  GOTCHA_BINDING_MACRO(MPI_File_iwrite_at, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_iwrite, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_iwrite_shared, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_open, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_read_all_begin, MPIIO);

  GOTCHA_BINDING_MACRO(MPI_File_read_all, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_read_at_all, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_read_at_all_begin, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_read_at, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_read, MPIIO);

  GOTCHA_BINDING_MACRO(MPI_File_read_ordered_begin, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_read_ordered, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_read_shared, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_sync, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_write_all_begin, MPIIO);

  GOTCHA_BINDING_MACRO(MPI_File_write_all, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_write_at_all_begin, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_write_at_all, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_write_at, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_write, MPIIO);

  GOTCHA_BINDING_MACRO(MPI_File_write_ordered_begin, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_write_ordered, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_write_shared, MPIIO);
  GOTCHA_BINDING_MACRO(MPI_File_delete, MPIIO);
  num_bindings = bindings.size();
  if (num_bindings > 0) {
    char tool_name[64];
    sprintf(tool_name, "%s_mpiio", name);
    gotcha_binding_t *raw_bindings = bindings.data();
    gotcha_wrap(raw_bindings, num_bindings, tool_name);
    gotcha_set_priority(tool_name, priority);
  }
  return num_bindings;
}
#endif  // BRAHMA_ENABLE_MPI
#endif  // BRAHMA_MPIIO_H
