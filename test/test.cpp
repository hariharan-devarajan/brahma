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
#include <sys/mman.h>

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
  POSIXTest() : api_count(0) {}
  virtual ~POSIXTest() {}
  static std::shared_ptr<POSIXTest> get_instance() {
    if (instance == nullptr) {
      instance = std::make_shared<POSIXTest>();
      POSIX::set_instance(instance);
    }
    return instance;
  }
  size_t api_count;

  int open(const char *pathname, int flags, ...) override {
    api_count++;
    return 0;
  }

  int creat64(const char *path, mode_t mode) override {
    api_count++;
    return 0;
  }

  int open64(const char *path, int flags, ...) override {
    api_count++;
    return 0;
  }

  int close(int fd) override {
    api_count++;
    return 0;
  }

  ssize_t write(int fd, const void *buf, size_t count) override {
    api_count++;
    return 0;
  }

  ssize_t read(int fd, void *buf, size_t count) override {
    api_count++;
    return 0;
  }

  off_t lseek(int fd, off_t offset, int whence) override {
    api_count++;
    return 0;
  }

  off64_t lseek64(int fd, off64_t offset, int whence) override {
    api_count++;
    return 0;
  }

  ssize_t pread(int fd, void *buf, size_t count, off_t offset) override {
    api_count++;
    return 0;
  }

  ssize_t pread64(int fd, void *buf, size_t count, off64_t offset) override {
    api_count++;
    return 0;
  }

  ssize_t pwrite(int fd, const void *buf, size_t count,
                 off64_t offset) override {
    api_count++;
    return 0;
  }

  ssize_t pwrite64(int fd, const void *buf, size_t count,
                   off64_t offset) override {
    api_count++;
    return 0;
  }

  int fsync(int fd) override {
    api_count++;
    return 0;
  }

  int fdatasync(int fd) override {
    api_count++;
    return 0;
  }

  int openat(int dirfd, const char *pathname, int flags, ...) override {
    api_count++;
    return 0;
  }

  void *mmap(void *addr, size_t length, int prot, int flags, int fd,
             off_t offset) override {
    api_count++;
    return 0;
  }

  void *mmap64(void *addr, size_t length, int prot, int flags, int fd,
               off64_t offset) override {
    api_count++;
    return 0;
  }

  int __xstat(int vers, const char *path, struct stat *buf) override {
    api_count++;
    return 0;
  }

  int __xstat64(int vers, const char *path, struct stat64 *buf) override {
    api_count++;
    return 0;
  }

  int __lxstat(int vers, const char *path, struct stat *buf) override {
    api_count++;
    return 0;
  }

  int __lxstat64(int vers, const char *path, struct stat64 *buf) override {
    api_count++;
    return 0;
  }

  int __fxstat(int vers, int fd, struct stat *buf) override {
    api_count++;
    return 0;
  }

  int __fxstat64(int vers, int fd, struct stat64 *buf) override {
    api_count++;
    return 0;
  }

  char *getcwd(char *buf, size_t size) override {
    api_count++;
    return 0;
  }

  int mkdir(const char *pathname, mode_t mode) override {
    api_count++;
    return 0;
  }

  int rmdir(const char *pathname) override {
    api_count++;
    return 0;
  }

  int chdir(const char *path) override {
    api_count++;
    return 0;
  }

  int link(const char *oldpath, const char *newpath) override {
    api_count++;
    return 0;
  }

  int linkat(int fd1, const char *path1, int fd2, const char *path2,
             int flag) override {
    api_count++;
    return 0;
  }

  int unlink(const char *pathname) override {
    api_count++;
    return 0;
  }

  int symlink(const char *path1, const char *path2) override {
    api_count++;
    return 0;
  }

  int symlinkat(const char *path1, int fd, const char *path2) override {
    api_count++;
    return 0;
  }

  ssize_t readlink(const char *path, char *buf, size_t bufsize) override {
    api_count++;
    return 0;
  }
  ssize_t readlinkat(int fd, const char *path, char *buf,
                     size_t bufsize) override {
    api_count++;
    return 0;
  }

  int rename(const char *oldpath, const char *newpath) override {
    api_count++;
    return 0;
  }

  int chmod(const char *path, mode_t mode) override {
    api_count++;
    return 0;
  }

  int chown(const char *path, uid_t owner, gid_t group) override {
    api_count++;
    return 0;
  }

  int lchown(const char *path, uid_t owner, gid_t group) override {
    api_count++;
    return 0;
  }

  int utime(const char *filename, const utimbuf *buf) override {
    api_count++;
    return 0;
  }

  DIR *opendir(const char *name) override {
    api_count++;
    return 0;
  }

  dirent *readdir(DIR *dir) override {
    api_count++;
    return 0;
  }
  int closedir(DIR *dir) override {
    api_count++;
    return 0;
  }

  void rewinddir(DIR *dir) override { api_count++; }

  int fcntl(int fd, int cmd, ...) override {
    api_count++;
    return 0;
  }

  int dup(int oldfd) override {
    api_count++;
    return 0;
  }

  int dup2(int oldfd, int newfd) override {
    api_count++;
    return 0;
  }

  int pipe(int pipefd[2]) override {
    api_count++;
    return 0;
  }
  int mkfifo(const char *pathname, mode_t mode) override {
    api_count++;
    return 0;
  }

  mode_t umask(mode_t mask) override {
    api_count++;
    return 0;
  }

  int access(const char *path, int amode) override {
    api_count++;
    return 0;
  }

  int faccessat(int fd, const char *path, int amode, int flag) override {
    api_count++;
    return 0;
  }

  int remove(const char *pathname) override {
    api_count++;
    return 0;
  }

  int truncate(const char *pathname, off_t length) override {
    api_count++;
    return 0;
  }

  int ftruncate(int fd, off_t length) override {
    api_count++;
    return 0;
  }

  int execl(const char *pathname, const char *arg, ...) override {
    api_count++;
    return 0;
  }

  int execlp(const char *file, const char *arg, ...) override {
    api_count++;
    return 0;
  }

  int execv(const char *pathname, char *const argv[]) override {
    api_count++;
    return 0;
  }

  int execvp(const char *file, char *const argv[]) override {
    api_count++;
    return 0;
  }

  int execvpe(const char *file, char *const argv[],
              char *const envp[]) override {
    api_count++;
    return 0;
  }

  int fork() override {
    api_count++;
    return 0;
  }
};
class STDIOTest : public STDIO {
 private:
  static std::shared_ptr<STDIOTest> instance;

 public:
  STDIOTest() : api_count(0) {}

  ~STDIOTest() {}
  static std::shared_ptr<STDIOTest> get_instance() {
    if (instance == nullptr) {
      instance = std::make_shared<STDIOTest>();
      STDIOTest::set_instance(instance);
    }
    return instance;
  }
  size_t api_count;

  FILE *fopen(const char *path, const char *mode) override {
    api_count++;
    return 0;
  }
  FILE *fopen64(const char *path, const char *mode) override {
    api_count++;
    return 0;
  }
  int fclose(FILE *fp) override {
    api_count++;
    return 0;
  }
  size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) override {
    api_count++;
    return 0;
  }
  size_t fwrite(const void *ptr, size_t size, size_t nmemb,
                FILE *stream) override {
    api_count++;
    return 0;
  }
  long ftell(FILE *fp) override {
    api_count++;
    return 0;
  }
  int fseek(FILE *stream, long offset, int whence) override {
    api_count++;
    return 0;
  }
  FILE *fdopen(int fd, const char *mode) override {
    api_count++;
    return 0;
  }
  int fileno(FILE *stream) override {
    api_count++;
    return 0;
  }
  FILE *tmpfile(void) override {
    api_count++;
    return 0;
  }
  int fseeko(FILE *stream, off_t offset, int whence) override {
    api_count++;
    return 0;
  }
  off_t ftello(FILE *stream) override {
    api_count++;
    return 0;
  }
};
#ifdef BRAHMA_ENABLE_MPI
class MPIIOTest : public MPIIO {
 private:
  static std::shared_ptr<MPIIOTest> instance;

 public:
  MPIIOTest() : api_count(0) {}

  ~MPIIOTest() {}
  static std::shared_ptr<MPIIOTest> get_instance() {
    if (instance == nullptr) {
      instance = std::make_shared<MPIIOTest>();
      MPIIOTest::set_instance(instance);
    }
    return instance;
  }
  size_t api_count;

  int MPI_File_close(MPI_File *fh) override {
    api_count++;
    return 0;
  }

  int MPI_File_set_size(MPI_File fh, MPI_Offset size) override {
    api_count++;
    return 0;
  }

  int MPI_File_iread_at(MPI_File fh, MPI_Offset offset, void *buf, int count,
                        MPI_Datatype datatype, MPI_Request *request) override {
    api_count++;
    return 0;
  }

  int MPI_File_iread(MPI_File fh, void *buf, int count, MPI_Datatype datatype,
                     MPI_Request *request) override {
    api_count++;
    return 0;
  }

  int MPI_File_iread_shared(MPI_File fh, void *buf, int count,
                            MPI_Datatype datatype,
                            MPI_Request *request) override {
    api_count++;
    return 0;
  }

  int MPI_File_iwrite_at(MPI_File fh, MPI_Offset offset, const void *buf,
                         int count, MPI_Datatype datatype,
                         MPI_Request *request) override {
    api_count++;
    return 0;
  }

  int MPI_File_iwrite(MPI_File fh, const void *buf, int count,
                      MPI_Datatype datatype, MPI_Request *request) override {
    api_count++;
    return 0;
  }

  int MPI_File_iwrite_shared(MPI_File fh, const void *buf, int count,
                             MPI_Datatype datatype,
                             MPI_Request *request) override {
    api_count++;
    return 0;
  }

  int MPI_File_open(MPI_Comm comm, const char *filename, int amode,
                    MPI_Info info, MPI_File *fh) override {
    api_count++;
    return 0;
  }

  int MPI_File_read_all_begin(MPI_File fh, void *buf, int count,
                              MPI_Datatype datatype) override {
    api_count++;
    return 0;
  }

  int MPI_File_read_all(MPI_File fh, void *buf, int count,
                        MPI_Datatype datatype, MPI_Status *status) override {
    api_count++;
    return 0;
  }

  int MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count,
                           MPI_Datatype datatype, MPI_Status *status) override {
    api_count++;
    return 0;
  }

  int MPI_File_read_at_all_begin(MPI_File fh, MPI_Offset offset, void *buf,
                                 int count, MPI_Datatype datatype) override {
    api_count++;
    return 0;
  }

  int MPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf, int count,
                       MPI_Datatype datatype, MPI_Status *status) override {
    api_count++;
    return 0;
  }

  int MPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype datatype,
                    MPI_Status *status) override {
    api_count++;
    return 0;
  }

  int MPI_File_read_ordered_begin(MPI_File fh, void *buf, int count,
                                  MPI_Datatype datatype) override {
    api_count++;
    return 0;
  }

  int MPI_File_read_ordered(MPI_File fh, void *buf, int count,
                            MPI_Datatype datatype,
                            MPI_Status *status) override {
    api_count++;
    return 0;
  }

  int MPI_File_read_shared(MPI_File fh, void *buf, int count,
                           MPI_Datatype datatype, MPI_Status *status) override {
    api_count++;
    return 0;
  }

  int MPI_File_sync(MPI_File fh) override {
    api_count++;
    return 0;
  }

  int MPI_File_write_all_begin(MPI_File fh, const void *buf, int count,
                               MPI_Datatype datatype) override {
    api_count++;
    return 0;
  }

  int MPI_File_write_all(MPI_File fh, const void *buf, int count,
                         MPI_Datatype datatype, MPI_Status *status) override {
    api_count++;
    return 0;
  }

  int MPI_File_write_at_all_begin(MPI_File fh, MPI_Offset offset,
                                  const void *buf, int count,
                                  MPI_Datatype datatype) override {
    api_count++;
    return 0;
  }

  int MPI_File_write_at_all(MPI_File fh, MPI_Offset offset, const void *buf,
                            int count, MPI_Datatype datatype,
                            MPI_Status *status) override {
    api_count++;
    return 0;
  }

  int MPI_File_write_at(MPI_File fh, MPI_Offset offset, const void *buf,
                        int count, MPI_Datatype datatype,
                        MPI_Status *status) override {
    api_count++;
    return 0;
  }

  int MPI_File_write(MPI_File fh, const void *buf, int count,
                     MPI_Datatype datatype, MPI_Status *status) override {
    api_count++;
    return 0;
  }

  int MPI_File_write_ordered_begin(MPI_File fh, const void *buf, int count,
                                   MPI_Datatype datatype) override {
    api_count++;
    return 0;
  }

  int MPI_File_write_ordered(MPI_File fh, const void *buf, int count,
                             MPI_Datatype datatype,
                             MPI_Status *status) override {
    api_count++;
    return 0;
  }

  int MPI_File_write_shared(MPI_File fh, const void *buf, int count,
                            MPI_Datatype datatype,
                            MPI_Status *status) override {
    api_count++;
    return 0;
  }
  int MPI_File_delete(const char *filename, MPI_Info info) override {
    api_count++;
    return 0;
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
  auto posix = brahma::POSIXTest::get_instance();
  posix->bind<brahma::POSIXTest>("tool", 1);
  auto stdio = brahma::STDIOTest::get_instance();
  stdio->bind<brahma::STDIOTest>("tool", 1);
#ifdef BRAHMA_ENABLE_MPI
  auto mpiio = brahma::MPIIOTest::get_instance();
  mpiio->bind<brahma::MPIIOTest>("tool", 1);
#endif
}
void __attribute__((destructor)) test_finalize() {
  auto posix = brahma::POSIXTest::get_instance();
  posix->unbind();
  assert(posix->num_bindings == posix->api_count);
  auto stdio = brahma::STDIOTest::get_instance();
  stdio->unbind();
  assert(stdio->num_bindings == stdio->api_count);
#ifdef BRAHMA_ENABLE_MPI
  auto mpiio = brahma::MPIIOTest::get_instance();
  mpiio->unbind();
  assert(mpiio->num_bindings == mpiio->api_count);
#endif
}

int main(int argc, char *argv[]) {
  open("", 0);

  creat64("", 0);

  open64("", 0);

  close(0);

  write(0, NULL, 0);

  read(0, NULL, 0);

  lseek(0, 0, 0);

  lseek64(0, 0, 0);

  pread(0, NULL, 0, 0);

  pread64(0, NULL, 0, 0);

  pwrite(0, NULL, 0, 0);

  pwrite64(0, NULL, 0, 0);

  fsync(0);

  fdatasync(0);

  openat(0, "", 0);

  mmap(NULL, 0, 0, 0, 0, 0);

  mmap64(NULL, 0, 0, 0, 0, 0);

  stat("", NULL);

  getcwd(NULL, 0);

  mkdir("", 0);

  rmdir("");

  chdir("");

  link("", "");

  linkat(01, "", 0, "", 0);

  unlink("");

  symlink("", "");

  symlinkat("", 0, "");

  readlink("", NULL, 0);

  readlinkat(0, "", NULL, 0);

  rename("", "");

  chmod("", 0);

  chown("", 0, 0);

  lchown("", 0, 0);

  utime("", NULL);

  opendir("");

  readdir(NULL);

  closedir(NULL);

  rewinddir(NULL);

  fcntl(0, 0);

  dup(0);

  dup2(0, 0);

  pipe(NULL);

  mkfifo("", 0);

  umask(0);

  access("", 0);

  faccessat(0, "", 0, 0);

  remove("");

  truncate("", 0);

  ftruncate(0, 0);

  execl("", "");

  execlp("", "");

  execv("", NULL);

  execvp("", NULL);

  execvpe("", NULL, NULL);

  fork();

  fopen("", "");
  fopen64("", "");
  fclose(NULL);
  fread(NULL, 0, 0, NULL);
  fwrite(NULL, 0, 0, NULL);
  ftell(NULL);
  fseek(NULL, 0, 0);
  fdopen(0, "");
  fileno(NULL);
  tmpfile();
  fseeko(NULL, 0, 0);
  ftello(NULL);

#ifdef BRAHMA_ENABLE_MPI

  MPI_File_close(NULL);

  MPI_File_set_size(NULL, 0);

  MPI_File_iread_at(NULL, 0, NULL, 0, 0, NULL);

  MPI_File_iread(NULL, NULL, 0, 0, NULL);

  MPI_File_iread_shared(NULL, NULL, 0, 0, NULL);

  MPI_File_iwrite_at(NULL, 0, NULL, 0, 0, NULL);

  MPI_File_iwrite(NULL, NULL, 0, 0, NULL);

  MPI_File_iwrite_shared(NULL, NULL, 0, 0, NULL);

  MPI_File_open(NULL, NULL, 0, NULL, NULL);

  MPI_File_read_all_begin(NULL, NULL, 0, 0);

  MPI_File_read_all(NULL, NULL, 0, 0, NULL);

  MPI_File_read_at_all(NULL, 0, NULL, 0, 0, NULL);

  MPI_File_read_at_all_begin(NULL, 0, NULL, 0, 0);

  MPI_File_read_at(NULL, 0, NULL, 0, 0, NULL);

  MPI_File_read(NULL, NULL, 0, 0, NULL);

  MPI_File_read_ordered_begin(NULL, NULL, 0, 0);

  MPI_File_read_ordered(NULL, NULL, 0, 0, NULL);

  MPI_File_read_shared(NULL, NULL, 0, 0, NULL);

  MPI_File_sync(NULL);

  MPI_File_write_all_begin(NULL, NULL, 0, 0);

  MPI_File_write_all(NULL, NULL, 0, 0, NULL);

  MPI_File_write_at_all_begin(NULL, 0, NULL, 0, 0);

  MPI_File_write_at_all(NULL, 0, NULL, 0, 0, NULL);

  MPI_File_write_at(NULL, 0, NULL, 0, 0, NULL);

  MPI_File_write(NULL, NULL, 0, 0, NULL);

  MPI_File_write_ordered_begin(NULL, NULL, 0, 0);

  MPI_File_write_ordered(NULL, NULL, 0, 0, NULL);

  MPI_File_write_shared(NULL, NULL, 0, 0, NULL);
  MPI_File_delete(NULL, NULL);
#endif
  return 0;
}