//
// Created by hariharan on 8/16/22.
//
#include <brahma/interface/mpiio.h>

#include <stdexcept>
#ifdef BRAHMA_ENABLE_MPI

namespace brahma {
std::shared_ptr<MPIIO> MPIIO::my_instance = nullptr;

std::shared_ptr<MPIIO> MPIIO::get_instance() {
  if (my_instance == nullptr) {
    BRAHMA_LOG_INFO("MPIIO class not intercepted but used", "");
    my_instance = std::make_shared<MPIIO>();
  }
  return my_instance;
}

int MPIIO::set_instance(std::shared_ptr<MPIIO> instance_i) {
  if (instance_i != nullptr) {
    my_instance = instance_i;
    return 0;
  } else {
    BRAHMA_LOG_ERROR("%s instance_i is not set", "MPIIO");
    throw std::runtime_error("instance_i is not set");
  }
}

int MPIIO::MPI_File_close(MPI_File *fh) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_close, int, (fh));
  return result;
}

int MPIIO::MPI_File_set_size(MPI_File fh, MPI_Offset size) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_set_size, int, (fh, size));
  return result;
}

int MPIIO::MPI_File_iread_at(MPI_File fh, MPI_Offset offset, void *buf,
                             int count, MPI_Datatype datatype,
                             MPI_Request *request) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_iread_at, int,
                        (fh, offset, buf, count, datatype, request));
  return result;
}

int MPIIO::MPI_File_iread(MPI_File fh, void *buf, int count,
                          MPI_Datatype datatype, MPI_Request *request) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_iread, int,
                        (fh, buf, count, datatype, request));
  return result;
}

int MPIIO::MPI_File_iread_shared(MPI_File fh, void *buf, int count,
                                 MPI_Datatype datatype, MPI_Request *request) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_iread_shared, int,
                        (fh, buf, count, datatype, request));
  return result;
}

int MPIIO::MPI_File_iwrite_at(MPI_File fh, MPI_Offset offset, const void *buf,
                              int count, MPI_Datatype datatype,
                              MPI_Request *request) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_iwrite_at, int,
                        (fh, offset, buf, count, datatype, request));
  return result;
}

int MPIIO::MPI_File_iwrite(MPI_File fh, const void *buf, int count,
                           MPI_Datatype datatype, MPI_Request *request) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_iwrite, int,
                        (fh, buf, count, datatype, request));
  return result;
}

int MPIIO::MPI_File_iwrite_shared(MPI_File fh, const void *buf, int count,
                                  MPI_Datatype datatype, MPI_Request *request) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_iwrite_shared, int,
                        (fh, buf, count, datatype, request));
  return result;
}

int MPIIO::MPI_File_open(MPI_Comm comm, const char *filename, int amode,
                         MPI_Info info, MPI_File *fh) {
  utility->exclude_file(filename, brahma::InterfaceType::INTERFACE_POSIX);
  BRAHMA_UNWRAPPED_FUNC(MPI_File_open, int, (comm, filename, amode, info, fh));
  utility->include_file(filename, brahma::InterfaceType::INTERFACE_POSIX);
  return result;
}

int MPIIO::MPI_File_read_all_begin(MPI_File fh, void *buf, int count,
                                   MPI_Datatype datatype) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_read_all_begin, int,
                        (fh, buf, count, datatype));
  return result;
}

int MPIIO::MPI_File_read_all(MPI_File fh, void *buf, int count,
                             MPI_Datatype datatype, MPI_Status *status) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_read_all, int,
                        (fh, buf, count, datatype, status));
  return result;
}

int MPIIO::MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf,
                                int count, MPI_Datatype datatype,
                                MPI_Status *status) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_read_at_all, int,
                        (fh, offset, buf, count, datatype, status));
  return result;
}

int MPIIO::MPI_File_read_at_all_begin(MPI_File fh, MPI_Offset offset, void *buf,
                                      int count, MPI_Datatype datatype) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_read_at_all_begin, int,
                        (fh, offset, buf, count, datatype));
  return result;
}

int MPIIO::MPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf,
                            int count, MPI_Datatype datatype,
                            MPI_Status *status) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_read_at, int,
                        (fh, offset, buf, count, datatype, status));
  return result;
}

int MPIIO::MPI_File_read(MPI_File fh, void *buf, int count,
                         MPI_Datatype datatype, MPI_Status *status) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_read, int, (fh, buf, count, datatype, status));
  return result;
}

int MPIIO::MPI_File_read_ordered_begin(MPI_File fh, void *buf, int count,
                                       MPI_Datatype datatype) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_read_ordered_begin, int,
                        (fh, buf, count, datatype));
  return result;
}

int MPIIO::MPI_File_read_ordered(MPI_File fh, void *buf, int count,
                                 MPI_Datatype datatype, MPI_Status *status) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_read_ordered, int,
                        (fh, buf, count, datatype, status));
  return result;
}

int MPIIO::MPI_File_read_shared(MPI_File fh, void *buf, int count,
                                MPI_Datatype datatype, MPI_Status *status) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_read_shared, int,
                        (fh, buf, count, datatype, status));
  return result;
}

int MPIIO::MPI_File_sync(MPI_File fh) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_sync, int, (fh));
  return result;
}

int MPIIO::MPI_File_write_all_begin(MPI_File fh, const void *buf, int count,
                                    MPI_Datatype datatype) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_write_all_begin, int,
                        (fh, buf, count, datatype));
  return result;
}

int MPIIO::MPI_File_write_all(MPI_File fh, const void *buf, int count,
                              MPI_Datatype datatype, MPI_Status *status) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_write_all, int,
                        (fh, buf, count, datatype, status));
  return result;
}

int MPIIO::MPI_File_write_at_all_begin(MPI_File fh, MPI_Offset offset,
                                       const void *buf, int count,
                                       MPI_Datatype datatype) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_write_at_all_begin, int,
                        (fh, offset, buf, count, datatype));
  return result;
}

int MPIIO::MPI_File_write_at_all(MPI_File fh, MPI_Offset offset,
                                 const void *buf, int count,
                                 MPI_Datatype datatype, MPI_Status *status) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_write_at_all, int,
                        (fh, offset, buf, count, datatype, status));
  return result;
}

int MPIIO::MPI_File_write_at(MPI_File fh, MPI_Offset offset, const void *buf,
                             int count, MPI_Datatype datatype,
                             MPI_Status *status) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_write_at, int,
                        (fh, offset, buf, count, datatype, status));
  return result;
}

int MPIIO::MPI_File_write(MPI_File fh, const void *buf, int count,
                          MPI_Datatype datatype, MPI_Status *status) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_write, int,
                        (fh, buf, count, datatype, status));
  return result;
}

int MPIIO::MPI_File_write_ordered_begin(MPI_File fh, const void *buf, int count,
                                        MPI_Datatype datatype) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_write_ordered_begin, int,
                        (fh, buf, count, datatype));
  return result;
}

int MPIIO::MPI_File_write_ordered(MPI_File fh, const void *buf, int count,
                                  MPI_Datatype datatype, MPI_Status *status) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_write_ordered, int,
                        (fh, buf, count, datatype, status));
  return result;
}

int MPIIO::MPI_File_write_shared(MPI_File fh, const void *buf, int count,
                                 MPI_Datatype datatype, MPI_Status *status) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_write_shared, int,
                        (fh, buf, count, datatype, status));
  return result;
}

int MPIIO::MPI_File_delete(const char *filename, MPI_Info info) {
  BRAHMA_UNWRAPPED_FUNC(MPI_File_delete, int, (filename, info));
  return result;
}
}  // namespace brahma
#endif  // BRAHMA_ENABLE_MPI