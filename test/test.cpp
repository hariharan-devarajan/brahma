//
// Created by hariharan on 8/8/22.
//
/* Brahma Header */
#include <brahma/brahma.h>
/* External Headers*/
#include <assert.h>
#include <brahma/brahma.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <utime.h>
#ifdef BRAHMA_ENABLE_MPI
#include <mpi.h>

#define LEN 10

#define CHECK_ERR(func)                                              \
  {                                                                  \
    if (err != MPI_SUCCESS) {                                        \
      int errorStringLen;                                            \
      char errorString[MPI_MAX_ERROR_STRING];                        \
      MPI_Error_string(err, errorString, &errorStringLen);           \
      printf("Error at line %d: calling %s (%s)\n", __LINE__, #func, \
             errorString);                                           \
    }                                                                \
  }
#endif
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

std::shared_ptr<POSIXTest> POSIXTest::instance = nullptr;
std::shared_ptr<STDIOTest> STDIOTest::instance = nullptr;
#ifdef BRAHMA_ENABLE_MPI
std::shared_ptr<MPIIOTest> MPIIOTest::instance = nullptr;
#endif
}  // namespace brahma

void __attribute__((constructor)) test_init() {
  brahma_gotcha_wrap("tool", 1);
  brahma::POSIXTest::get_instance();
  brahma::STDIOTest::get_instance();
}
void __attribute__((destructor)) test_finalize() {}

int main(int argc, char* argv[]) {
#ifdef BRAHMA_ENABLE_MPI
  MPI_Init(&argc, &argv);
#endif

  char filename[1024];
  sprintf(filename, "%s/demofile.txt", argv[1]);
  char filename_link[1024];
  sprintf(filename_link, "%s/demofile_link.txt", argv[1]);
  truncate(filename, 0);
  FILE* fh = fopen(filename, "w+");
  if (fh != nullptr) {
    fwrite("hello", sizeof("hello"), 1, fh);
    fclose(fh);
  }
  link(filename, filename_link);
  unlink(filename_link);
  symlink(filename, filename_link);
  chmod(filename, S_ISUID);
  chown(filename, 0, 0);
  lchown(filename, 0, 0);
  struct utimbuf utimbuf1;
  utime(filename, &utimbuf1);
  char dir[1024];
  sprintf(dir, "%s", argv[1]);
  int dd = open(dir, O_PATH);
  fcntl(dd, F_DUPFD);
  fcntl(dd, F_GETFD);
  fcntl(dd, F_GETOWN_EX);
  int dd2 = 1;
  dup2(dd, dd2);
  (void)dd2;
  umask(0);
  mkfifo(filename, 0);
  symlinkat(filename, dd, filename_link);
  faccessat(dd, "demofile.txt", O_RDONLY, 0);
  linkat(dd, "demofile.txt", dd, "demofile_link2.txt", 0);
  chdir(dir);
  int fd = openat(dd, "demofile.txt", O_RDONLY);
  if (fd != -1) close(fd);
  fd = openat(dd, "demofile2.txt", O_WRONLY | O_CREAT, 777);
  if (fd != -1) close(fd);
  close(dd);
  sprintf(filename, "%s/demofile2.txt", argv[1]);
  fd = creat64(filename, O_RDWR);
  if (fd != -1) close(fd);
  fd = open(filename, O_RDWR);
  int set_offset = lseek(fd, 1, SEEK_SET);
  (void)set_offset;
  char buf[1];
  pread(fd, buf, 1, 1);
  pread64(fd, buf, 1, 1);
  pwrite(fd, buf, 1, 1);
  pwrite64(fd, buf, 1, 1);
  fsync(fd);
  fdatasync(fd);
  readlinkat(fd, filename, buf, 1);
  ftruncate(fd, 0);
  close(fd);
  remove(filename);
  remove(filename_link);
  remove("demofile_link2.txt");

#ifdef BRAHMA_ENABLE_MPI

  int err, rank, nprocs, cmode, omode;
  MPI_File mpi_fh;
  MPI_Info info;

  err = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  CHECK_ERR(MPI_Comm_rank);
  err = MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  CHECK_ERR(MPI_Comm_size);

  const char* mpi_filename = "testfile.out";

  /* Users can set customized I/O hints in info object */
  info = MPI_INFO_NULL; /* no user I/O hint */

  /* set file open mode */
  cmode = MPI_MODE_CREATE;  /* to create a new file */
  cmode |= MPI_MODE_WRONLY; /* with write-only permission */

  /* collectively open a file, shared by all processes in MPI_COMM_WORLD */
  err = MPI_File_open(MPI_COMM_WORLD, mpi_filename, cmode, info, &mpi_fh);
  CHECK_ERR(MPI_File_open to write);

  /* collectively close the file */
  err = MPI_File_close(&mpi_fh);
  CHECK_ERR(MPI_File_close);

  /* set file open mode */
  omode = MPI_MODE_RDONLY; /* with read-only permission */

  /* collectively open a file, shared by all processes in MPI_COMM_WORLD */
  err = MPI_File_open(MPI_COMM_WORLD, mpi_filename, omode, info, &mpi_fh);
  CHECK_ERR(MPI_File_open to read);

  /* collectively close the file */
  err = MPI_File_close(&mpi_fh);
  CHECK_ERR(MPI_File_close);

  MPI_Finalize();
#endif
  return 0;
}