//
// Created by Izzet Yildirim <iyildirim@hawk.iit.edu> on 9/4/24.
//
#include <brahma/brahma.h>

#include <iostream>
#ifdef BRAHMA_ENABLE_HDF5
#include <hdf5.h>

namespace brahma {
class HDF5Test : public HDF5 {
 private:
  static std::shared_ptr<HDF5Test> instance;

 public:
  HDF5Test() : api_count(0) {}

  virtual ~HDF5Test() {}

  static std::shared_ptr<HDF5Test> get_instance() {
    if (instance == nullptr) {
      instance = std::make_shared<HDF5Test>();
      HDF5::set_instance(instance);
    }
    return instance;
  }

  size_t api_count;

#if BRAHMA_HDF5_VERSION >= 100800
  hid_t H5Fcreate(const char* filename, unsigned int flags, hid_t fcpl_id,
                  hid_t fapl_id) override {
    api_count++;
    return HDF5::H5Fcreate(filename, flags, fcpl_id, fapl_id);
  }

  hid_t H5Dcreate2(hid_t loc_id, const char* name, hid_t type_id,
                   hid_t space_id, hid_t lcpl_id, hid_t dcpl_id,
                   hid_t dapl_id) override {
    api_count++;
    return HDF5::H5Dcreate2(loc_id, name, type_id, space_id, lcpl_id, dcpl_id,
                            dapl_id);
  }

  hid_t H5Screate_simple(int rank, const hsize_t* current_dims,
                         const hsize_t* maximum_dims) override {
    api_count++;
    return HDF5::H5Screate_simple(rank, current_dims, maximum_dims);
  }

  herr_t H5Dwrite(hid_t dataset_id, hid_t mem_type_id, hid_t mem_space_id,
                  hid_t file_space_id, hid_t xfer_plist_id,
                  const void* buf) override {
    api_count++;
    return HDF5::H5Dwrite(dataset_id, mem_type_id, mem_space_id, file_space_id,
                          xfer_plist_id, buf);
  }

  herr_t H5Dread(hid_t dataset_id, hid_t mem_type_id, hid_t mem_space_id,
                 hid_t file_space_id, hid_t xfer_plist_id, void* buf) override {
    api_count++;
    return HDF5::H5Dread(dataset_id, mem_type_id, mem_space_id, file_space_id,
                         xfer_plist_id, buf);
  }

  herr_t H5Dclose(hid_t dataset_id) override {
    api_count++;
    return HDF5::H5Dclose(dataset_id);
  }

  herr_t H5Sclose(hid_t dataspace_id) override {
    api_count++;
    return HDF5::H5Sclose(dataspace_id);
  }

  herr_t H5Fclose(hid_t file_id) override {
    api_count++;
    return HDF5::H5Fclose(file_id);
  }
#endif
};

std::shared_ptr<HDF5Test> HDF5Test::instance = nullptr;

}  // namespace brahma

#endif

void __attribute__((constructor)) test_init() {
#ifdef BRAHMA_ENABLE_HDF5
  auto hdf5 = brahma::HDF5Test::get_instance();
  hdf5->bind<brahma::HDF5Test>("test", 0);
#endif
}

void __attribute__((destructor)) test_finalize() {
#ifdef BRAHMA_ENABLE_HDF5
  auto hdf5 = brahma::HDF5Test::get_instance();
  hdf5->unbind();
  std::cout << "HDF5 num_bindings: " << hdf5->num_bindings << std::endl;
  std::cout << "HDF5 api_count: " << hdf5->api_count << std::endl;
  assert(hdf5->num_bindings == hdf5->api_count);
#endif
}

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