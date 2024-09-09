//
// Created by Izzet Yildirim <iyildirim@hawk.iit.edu> on 9/4/24.
//
#include <brahma/brahma.h>
#ifdef BRAHMA_ENABLE_HDF5
#include <hdf5.h>

namespace brahma {
class POSIXTest : public POSIX {
 private:
  static std::shared_ptr<POSIXTest> instance;

 public:
  POSIXTest() {}
  static std::shared_ptr<POSIXTest> get_instance() {
    if (instance == nullptr) {
      instance = std::make_shared<POSIXTest>();
      POSIX::set_instance(instance);
    }
    return instance;
  }
};
class STDIOTest : public STDIO {
 private:
  static std::shared_ptr<STDIOTest> instance;

 public:
  STDIOTest() {}
  static std::shared_ptr<STDIOTest> get_instance() {
    if (instance == nullptr) {
      instance = std::make_shared<STDIOTest>();
      STDIOTest::set_instance(instance);
    }
    return instance;
  }
};
#ifdef BRAHMA_ENABLE_MPI
class MPIIOTest : public MPIIO {
 private:
  static std::shared_ptr<MPIIOTest> instance;

 public:
  MPIIOTest() {}
  static std::shared_ptr<MPIIOTest> get_instance() {
    if (instance == nullptr) {
      instance = std::make_shared<MPIIOTest>();
      MPIIOTest::set_instance(instance);
    }
    return instance;
  }
};
#endif
class HDF5Test : public HDF5 {
 private:
  static std::shared_ptr<HDF5Test> instance;

 public:
  HDF5Test() {}
  static std::shared_ptr<HDF5Test> get_instance() {
    if (instance == nullptr) {
      instance = std::make_shared<HDF5Test>();
      HDF5Test::set_instance(instance);
    }
    return instance;
  }
};
std::shared_ptr<POSIXTest> POSIXTest::instance = nullptr;
std::shared_ptr<STDIOTest> STDIOTest::instance = nullptr;
#ifdef BRAHMA_ENABLE_MPI
std::shared_ptr<MPIIOTest> MPIIOTest::instance = nullptr;
#endif
#ifdef BRAHMA_ENABLE_HDF5
std::shared_ptr<HDF5Test> HDF5Test::instance = nullptr;
#endif
}  // namespace brahma

#endif

void __attribute__((constructor)) test_init() {
  brahma_gotcha_wrap("tool", 1);
  brahma::POSIXTest::get_instance();
  brahma::STDIOTest::get_instance();
#ifdef BRAHMA_ENABLE_MPI
  brahma::MPIIOTest::get_instance();
#endif
  brahma::HDF5Test::get_instance();
}
void __attribute__((destructor)) test_finalize() { brahma_free_bindings(); }

int main(int argc, char* argv[]) {
#ifdef BRAHMA_ENABLE_HDF5
  const char* filename = "/tmp/test.h5";

  hid_t file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
  if (file_id < 0) {
    return 1;  // Error creating file
  }

  hsize_t dims[2] = {4, 6};
  hid_t dataspace_id = H5Screate_simple(2, dims, NULL);
  if (dataspace_id < 0) {
    H5Fclose(file_id);
    return 1;  // Error creating dataspace
  }

  hid_t dataset_id = H5Dcreate2(file_id, "/dset", H5T_NATIVE_INT, dataspace_id,
                                H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dataset_id < 0) {
    H5Sclose(dataspace_id);
    H5Fclose(file_id);
    return 1;  // Error creating dataset
  }

  int data[4][6] = {{0, 1, 2, 3, 4, 5},
                    {6, 7, 8, 9, 10, 11},
                    {12, 13, 14, 15, 16, 17},
                    {18, 19, 20, 21, 22, 23}};
  if (H5Dwrite(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT,
               data) < 0) {
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);
    return 1;  // Error writing data to dataset
  }

  int read_data[4][6];
  if (H5Dread(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT,
              read_data) < 0) {
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);
    return 1;  // Error reading data from dataset
  }

  H5Dclose(dataset_id);
  H5Sclose(dataspace_id);
  H5Fclose(file_id);
#endif
  return 0;
}