//
// Created by hariharan on 8/16/22.
//
#include <brahma/interface/posix.h>
#include <fcntl.h>
GOTCHA_MACRO_DEF(open, int, (const char *pathname, int flags, mode_t mode),
             (pathname, flags, mode), brahma::POSIX)

GOTCHA_MACRO_DEF(creat64, int, (const char *path, mode_t mode), (path, mode),
             brahma::POSIX)

GOTCHA_MACRO_DEF(open64, int, (const char *path, int flags, mode_t mode),
             (path, flags, mode), brahma::POSIX)

GOTCHA_MACRO_DEF(close, int, (int fd), (fd), brahma::POSIX)

GOTCHA_MACRO_DEF(write, ssize_t, (int fd, const void *buf, size_t count),
             (fd, buf, count), brahma::POSIX)

GOTCHA_MACRO_DEF(read, ssize_t, (int fd, void *buf, size_t count), (fd, buf, count),
             brahma::POSIX)

GOTCHA_MACRO_DEF(lseek, off_t, (int fd, off_t offset, int whence),
             (fd, offset, whence), brahma::POSIX)

GOTCHA_MACRO_DEF(lseek64, off64_t, (int fd, off64_t offset, int whence),
             (fd, offset, whence), brahma::POSIX)

GOTCHA_MACRO_DEF(pread, ssize_t, (int fd, void *buf, size_t count, off_t offset),
             (fd, buf, count, offset), brahma::POSIX)

GOTCHA_MACRO_DEF(pread64, ssize_t,
             (int fd, void *buf, size_t count, off64_t offset),
             (fd, buf, count, offset), brahma::POSIX)

GOTCHA_MACRO_DEF(pwrite, ssize_t,
             (int fd, const void *buf, size_t count, off_t offset),
             (fd, buf, count, offset), brahma::POSIX)

GOTCHA_MACRO_DEF(pwrite64, ssize_t,
             (int fd, const void *buf, size_t count, off64_t offset),
             (fd, buf, count, offset), brahma::POSIX)

GOTCHA_MACRO_DEF(fsync, int, (int fd), (fd), brahma::POSIX)

GOTCHA_MACRO_DEF(fdatasync, int, (int fd), (fd), brahma::POSIX)

GOTCHA_MACRO_DEF(openat, int,
             (int dirfd, const char *pathname, int flags, mode_t mode),
             (dirfd, pathname, flags, mode), brahma::POSIX)
GOTCHA_MACRO_DEF(mmap, void *,
             (void *addr, size_t length, int prot, int flags, int fd,
              off_t offset),
             (addr, length, prot, flags, fd, offset), brahma::POSIX)
GOTCHA_MACRO_DEF(mmap64, void *,
             (void *addr, size_t length, int prot, int flags, int fd,
              off64_t offset),
             (addr, length, prot, flags, fd, offset), brahma::POSIX)
GOTCHA_MACRO_DEF(__xstat, int, (int vers, const char *path, stat *buf),
             (vers, path, buf), brahma::POSIX)
GOTCHA_MACRO_DEF(__xstat64, int, (int vers, const char *path, stat64 *buf),
             (vers, path, buf), brahma::POSIX)
GOTCHA_MACRO_DEF(__lxstat, int, (int vers, const char *path, stat *buf),
             (vers, path, buf), brahma::POSIX)
GOTCHA_MACRO_DEF(__lxstat64, int, (int vers, const char *path, stat64 *buf),
             (vers, path, buf), brahma::POSIX)
GOTCHA_MACRO_DEF(__fxstat, int, (int vers, int fd, stat *buf), (vers, path, buf),
             brahma::POSIX)
GOTCHA_MACRO_DEF(__fxstat64, int, (int vers, int fd, stat64 *buf),
             (vers, path, buf), brahma::POSIX)
GOTCHA_MACRO_DEF(getcwd, char *, (char *buf, size_t size), (buf, size),
             brahma::POSIX)
GOTCHA_MACRO_DEF(mkdir, int, (const char *pathname, mode_t mode), (pathname, mode),
             brahma::POSIX)
GOTCHA_MACRO_DEF(rmdir, int, (const char *pathname), (pathname), brahma::POSIX)
GOTCHA_MACRO_DEF(chdir, int, (const char *path), (path), brahma::POSIX)
GOTCHA_MACRO_DEF(link, int, (const char *oldpath, const char *newpath),
             (oldpath, newpath), brahma::POSIX)
GOTCHA_MACRO_DEF(linkat, int,
             (int fd1, const char *path1, int fd2, const char *path2, int flag),
             (fd1, path1, fd2, path2, flag), brahma::POSIX)
GOTCHA_MACRO_DEF(unlink, int, (const char *pathname), (pathname), brahma::POSIX)
GOTCHA_MACRO_DEF(symlink, int, (const char *path1, const char *path2),
             (path1, path2), brahma::POSIX)
GOTCHA_MACRO_DEF(symlinkat, int, (const char *path1, int fd, const char *path2),
             (path1, fd, path2), brahma::POSIX)
GOTCHA_MACRO_DEF(readlink, ssize_t, (const char *path, char *buf, size_t bufsize),
             (path, buf, bufsize), brahma::POSIX)
GOTCHA_MACRO_DEF(readlinkat, ssize_t,
             (int fd, const char *path, char *buf, size_t bufsize),
             (fd, path, buf, bufsize), brahma::POSIX)
GOTCHA_MACRO_DEF(rename, int, (const char *oldpath, const char *newpath),
             (oldpath, newpath), brahma::POSIX)
GOTCHA_MACRO_DEF(chmod, int, (const char *path, mode_t mode), (path, mode),
             brahma::POSIX)
GOTCHA_MACRO_DEF(chown, int, (const char *path, uid_t owner, gid_t group),
             (path, owner, group), brahma::POSIX)
GOTCHA_MACRO_DEF(lchown, int, (const char *path, uid_t owner, gid_t group),
             (path, owner, group), brahma::POSIX)
GOTCHA_MACRO_DEF(utime, int, (const char *filename, const utimbuf *buf),
             (filename, buf), brahma::POSIX)
GOTCHA_MACRO_DEF(opendir, DIR *, (const char *name), (name), brahma::POSIX)
GOTCHA_MACRO_DEF(readdir, struct dirent *, (DIR * dir), (dir), brahma::POSIX)
GOTCHA_MACRO_DEF(closedir, int, (DIR * dir), (dir), brahma::POSIX)
GOTCHA_MACRO_DEF(rewinddir, void, (DIR * dir), (dir), brahma::POSIX)
GOTCHA_MACRO_DEF(fcntl, int, (int fd, int cmd, long arg), (fd, cmd, arg),
             brahma::POSIX)
GOTCHA_MACRO_DEF(dup, int, (int oldfd), (oldfd), brahma::POSIX)
GOTCHA_MACRO_DEF(dup2, int, (int oldfd, int newfd), (oldfd, newfd), brahma::POSIX)
GOTCHA_MACRO_DEF(pipe, int, (int pipefd[2]), (pipefd), brahma::POSIX)
GOTCHA_MACRO_DEF(mkfifo, int, (const char *pathname, mode_t mode), (pathname, mode),
             brahma::POSIX)
GOTCHA_MACRO_DEF(umask, mode_t, (mode_t mask), (mask), brahma::POSIX)
GOTCHA_MACRO_DEF(access, int, (const char *path, int amode), (path, amode),
             brahma::POSIX)
GOTCHA_MACRO_DEF(faccessat, int, (int fd, const char *path, int amode, int flag),
             (fd, path, amode, flag), brahma::POSIX)
GOTCHA_MACRO_DEF(remove, int, (const char *pathname), (pathname), brahma::POSIX)
GOTCHA_MACRO_DEF(truncate, int, (const char *pathname, off_t length),
             (pathname, length), brahma::POSIX)
GOTCHA_MACRO_DEF(ftruncate, int, (int fd, off_t length), (fd, length),
             brahma::POSIX)
GOTCHA_MACRO_DEF(execl, int, (const char *pathname, const char *arg, char *val),
             (pathname, arg, val), brahma::POSIX)
GOTCHA_MACRO_DEF(execlp, int, (const char *pathname, const char *arg, char *val),
             (pathname, arg, val), brahma::POSIX)
GOTCHA_MACRO_DEF(execv, int, (const char *pathname, char *const argv[]),
             (pathname, argv), brahma::POSIX)
GOTCHA_MACRO_DEF(execvp, int, (const char *pathname, char *const argv[]),
             (pathname, argv), brahma::POSIX)
GOTCHA_MACRO_DEF(execvpe, int,
             (const char *pathname, char *const argv[], char *const envp[]),
             (pathname, argv, envp), brahma::POSIX)
GOTCHA_MACRO_DEF(fork, int, (), (), brahma::POSIX)
namespace brahma {

std::shared_ptr<POSIX> POSIX::my_instance = nullptr;

std::shared_ptr<POSIX> POSIX::get_instance() {
  if (my_instance == nullptr) {
    BRAHMA_LOG_INFO("POSIX class not intercepted but used", "");
    my_instance = std::make_shared<POSIX>();
  }
  return my_instance;
}
int POSIX::set_instance(std::shared_ptr<POSIX> instance_i) {
  if (instance_i != nullptr) {
    my_instance = instance_i;
    return 0;
  } else {
    BRAHMA_LOG_ERROR("%s instance_i is not set", "POSIX");
    throw std::runtime_error("instance_i is not set");
  }
}

int POSIX::open(const char *pathname, int flags, ...) {
  if (flags & O_CREAT) {
    va_list args;
    va_start(args, flags);
    int mode = va_arg(args, int);
    va_end(args);
    BRAHMA_UNWRAPPED_FUNC(open, int, (pathname, flags, mode));
    return result;
  } else {
    BRAHMA_UNWRAPPED_FUNC(open, int, (pathname, flags));
    return result;
  }
}

int POSIX::creat64(const char *path, mode_t mode) {
  BRAHMA_UNWRAPPED_FUNC(creat64, int, (path, mode));
  return result;
}

int POSIX::open64(const char *path, int flags, ...) {
  if (flags & O_CREAT) {
    va_list args;
    va_start(args, flags);
    int mode = va_arg(args, int);
    va_end(args);
    BRAHMA_UNWRAPPED_FUNC(open64, int, (path, flags, mode));
    return result;
  } else {
    BRAHMA_UNWRAPPED_FUNC(open64, int, (path, flags));
    return result;
  }
}

int POSIX::close(int fd) {
  BRAHMA_UNWRAPPED_FUNC(close, int, (fd));
  return result;
}

ssize_t POSIX::write(int fd, const void *buf, size_t count) {
  BRAHMA_UNWRAPPED_FUNC(write, ssize_t, (fd, buf, count));
  return result;
}

ssize_t POSIX::read(int fd, void *buf, size_t count) {
  BRAHMA_UNWRAPPED_FUNC(read, ssize_t, (fd, buf, count));
  return result;
}

off_t POSIX::lseek(int fd, off_t offset, int whence) {
  BRAHMA_UNWRAPPED_FUNC(lseek, off_t, (fd, offset, whence));
  return result;
}

off64_t POSIX::lseek64(int fd, off64_t offset, int whence) {
  BRAHMA_UNWRAPPED_FUNC(lseek, off64_t, (fd, offset, whence));
  return result;
}

ssize_t POSIX::pread(int fd, void *buf, size_t count, off_t offset) {
  BRAHMA_UNWRAPPED_FUNC(pread, ssize_t, (fd, buf, count, offset));
  return result;
}

ssize_t POSIX::pread64(int fd, void *buf, size_t count, off64_t offset) {
  BRAHMA_UNWRAPPED_FUNC(pread64, ssize_t, (fd, buf, count, offset));
  return result;
}

ssize_t POSIX::pwrite(int fd, const void *buf, size_t count, off64_t offset) {
  BRAHMA_UNWRAPPED_FUNC(pwrite, ssize_t, (fd, buf, count, offset));
  return result;
}

ssize_t POSIX::pwrite64(int fd, const void *buf, size_t count, off64_t offset) {
  BRAHMA_UNWRAPPED_FUNC(pwrite64, ssize_t, (fd, buf, count, offset));
  return result;
}

int POSIX::fsync(int fd) {
  BRAHMA_UNWRAPPED_FUNC(fsync, int, (fd));
  return result;
}

int POSIX::fdatasync(int fd) {
  BRAHMA_UNWRAPPED_FUNC(fdatasync, int, (fd));
  return result;
}

int POSIX::openat(int dirfd, const char *pathname, int flags, ...) {
  if (flags & O_CREAT) {
    va_list args;
    va_start(args, flags);
    int mode = va_arg(args, int);
    va_end(args);
    BRAHMA_UNWRAPPED_FUNC(openat, int, (dirfd, pathname, flags, mode));
    return result;
  } else {
    BRAHMA_UNWRAPPED_FUNC(openat, int, (dirfd, pathname, flags));
    return result;
  }
}
void *POSIX::mmap(void *addr, size_t length, int prot, int flags, int fd,
                  off_t offset) {
  BRAHMA_UNWRAPPED_FUNC(mmap, void *, (addr, length, prot, flags, fd, offset));
  return result;
}

void *POSIX::mmap64(void *addr, size_t length, int prot, int flags, int fd,
                    off64_t offset) {
  BRAHMA_UNWRAPPED_FUNC(mmap64, void *,
                        (addr, length, prot, flags, fd, offset));
  return result;
}
int POSIX::__xstat(int vers, const char *path, struct stat *buf) {
  BRAHMA_UNWRAPPED_FUNC(__xstat, int, (vers, path, buf));
  return result;
}
int POSIX::__xstat64(int vers, const char *path, struct stat64 *buf) {
  BRAHMA_UNWRAPPED_FUNC(__xstat64, int, (vers, path, buf));
  return result;
}
int POSIX::__lxstat(int vers, const char *path, struct stat *buf) {
  BRAHMA_UNWRAPPED_FUNC(__lxstat, int, (vers, path, buf));
  return result;
}
int POSIX::__lxstat64(int vers, const char *path, struct stat64 *buf) {
  BRAHMA_UNWRAPPED_FUNC(__lxstat64, int, (vers, path, buf));
  return result;
}
int POSIX::__fxstat(int vers, int fd, struct stat *buf) {
  BRAHMA_UNWRAPPED_FUNC(__fxstat, int, (vers, fd, buf));
  return result;
}
int POSIX::__fxstat64(int vers, int fd, struct stat64 *buf) {
  BRAHMA_UNWRAPPED_FUNC(__fxstat64, int, (vers, fd, buf));
  return result;
}
char *POSIX::getcwd(char *buf, size_t size) {
  BRAHMA_UNWRAPPED_FUNC(getcwd, char *, (buf, size));
  return result;
}
int POSIX::mkdir(const char *pathname, mode_t mode) {
  BRAHMA_UNWRAPPED_FUNC(mkdir, int, (pathname, mode));
  return result;
}
int POSIX::rmdir(const char *pathname) {
  BRAHMA_UNWRAPPED_FUNC(rmdir, int, (pathname));
  return result;
}
int POSIX::chdir(const char *path) {
  BRAHMA_UNWRAPPED_FUNC(chdir, int, (path));
  return result;
}
int POSIX::link(const char *oldpath, const char *newpath) {
  BRAHMA_UNWRAPPED_FUNC(link, int, (oldpath, newpath));
  return result;
}
int POSIX::linkat(int fd1, const char *path1, int fd2, const char *path2,
                  int flag) {
  BRAHMA_UNWRAPPED_FUNC(linkat, int, (fd1, path1, fd2, path2, flag));
  return result;
}
int POSIX::unlink(const char *pathname) {
  BRAHMA_UNWRAPPED_FUNC(unlink, int, (pathname));
  return result;
}
int POSIX::symlink(const char *path1, const char *path2) {
  BRAHMA_UNWRAPPED_FUNC(symlink, int, (path1, path2));
  return result;
}
int POSIX::symlinkat(const char *path1, int fd, const char *path2) {
  BRAHMA_UNWRAPPED_FUNC(symlinkat, int, (path1, fd, path2));
  return result;
}
ssize_t POSIX::readlink(const char *path, char *buf, size_t bufsize) {
  BRAHMA_UNWRAPPED_FUNC(readlink, ssize_t, (path, buf, bufsize));
  return result;
}
ssize_t POSIX::readlinkat(int fd, const char *path, char *buf, size_t bufsize) {
  BRAHMA_UNWRAPPED_FUNC(readlinkat, ssize_t, (fd, path, buf, bufsize));
  return result;
}
int POSIX::rename(const char *oldpath, const char *newpath) {
  BRAHMA_UNWRAPPED_FUNC(rename, int, (oldpath, newpath));
  return result;
}
int POSIX::chmod(const char *path, mode_t mode) {
  BRAHMA_UNWRAPPED_FUNC(chmod, int, (path, mode));
  return result;
}
int POSIX::chown(const char *path, uid_t owner, gid_t group) {
  BRAHMA_UNWRAPPED_FUNC(chown, int, (path, owner, group));
  return result;
}
int POSIX::lchown(const char *path, uid_t owner, gid_t group) {
  BRAHMA_UNWRAPPED_FUNC(lchown, int, (path, owner, group));
  return result;
}
int POSIX::utime(const char *filename, const utimbuf *buf) {
  BRAHMA_UNWRAPPED_FUNC(utime, int, (filename, buf));
  return result;
}
DIR *POSIX::opendir(const char *name) {
  BRAHMA_UNWRAPPED_FUNC(opendir, DIR *, (name));
  return result;
}
dirent *POSIX::readdir(DIR *dir) {
  BRAHMA_UNWRAPPED_FUNC(readdir, dirent *, (dir));
  return result;
}
int POSIX::closedir(DIR *dir) {
  BRAHMA_UNWRAPPED_FUNC(closedir, int, (dir));
  return result;
}
void POSIX::rewinddir(DIR *dir) {
  BRAHMA_UNWRAPPED_FUNC_VOID(rewinddir, (dir));
}
int POSIX::fcntl(int fd, int cmd, ...) {
  if (cmd == F_DUPFD || cmd == F_DUPFD_CLOEXEC || cmd == F_SETFD ||
      cmd == F_SETFL || cmd == F_SETOWN) {  // arg: int
    va_list arg;
    va_start(arg, cmd);
    int val = va_arg(arg, int);
    va_end(arg);
    BRAHMA_UNWRAPPED_FUNC(fcntl, int, (fd, cmd, val));
    return result;
  } else if (cmd == F_GETFD || cmd == F_GETFL || cmd == F_GETOWN) {
    BRAHMA_UNWRAPPED_FUNC(fcntl, int, (fd, cmd));
    return result;
  } else if (cmd == F_SETLK || cmd == F_SETLKW || cmd == F_GETLK) {
    va_list arg;
    va_start(arg, cmd);
    struct flock *lk = va_arg(arg, struct flock *);
    va_end(arg);
    BRAHMA_UNWRAPPED_FUNC(fcntl, int, (fd, cmd, lk));
    return result;
  } else {  // assume arg: void, cmd==F_GETOWN_EX || cmd==F_SETOWN_EX
            // ||cmd==F_GETSIG || cmd==F_SETSIG)
    BRAHMA_UNWRAPPED_FUNC(fcntl, int, (fd, cmd));
    return result;
  }
}
int POSIX::dup(int oldfd) {
  BRAHMA_UNWRAPPED_FUNC(dup, int, (oldfd));
  return result;
}
int POSIX::dup2(int oldfd, int newfd) {
  BRAHMA_UNWRAPPED_FUNC(dup2, int, (oldfd, newfd));
  return result;
}
int POSIX::pipe(int pipefd[2]) {
  BRAHMA_UNWRAPPED_FUNC(pipe, int, (pipefd));
  return result;
}
int POSIX::mkfifo(const char *pathname, mode_t mode) {
  BRAHMA_UNWRAPPED_FUNC(mkfifo, int, (pathname, mode));
  return result;
}
mode_t POSIX::umask(mode_t mask) {
  BRAHMA_UNWRAPPED_FUNC(umask, mode_t, (mask));
  return result;
}

int POSIX::access(const char *path, int amode) {
  BRAHMA_UNWRAPPED_FUNC(access, int, (path, amode));
  return result;
}
int POSIX::faccessat(int fd, const char *path, int amode, int flag) {
  BRAHMA_UNWRAPPED_FUNC(faccessat, int, (fd, path, amode, flag));
  return result;
}

int POSIX::remove(const char *pathname) {
  BRAHMA_UNWRAPPED_FUNC(remove, int, (pathname));
  return result;
}
int POSIX::truncate(const char *pathname, off_t length) {
  BRAHMA_UNWRAPPED_FUNC(truncate, int, (pathname, length));
  return result;
}
int POSIX::ftruncate(int fd, off_t length) {
  BRAHMA_UNWRAPPED_FUNC(ftruncate, int, (fd, length));
  return result;
}
int POSIX::execl(const char *pathname, const char *arg, ...) {
  va_list args;
  va_start(args, arg);
  BRAHMA_UNWRAPPED_FUNC(execl, int, (pathname, arg, args));
  va_end(args);
  return result;
}
int POSIX::execlp(const char *pathname, const char *arg, ...) {
  va_list args;
  va_start(args, arg);
  BRAHMA_UNWRAPPED_FUNC(execlp, int, (pathname, arg, args));
  va_end(args);
  return result;
}
int POSIX::execv(const char *pathname, char *const argv[]) {
  BRAHMA_UNWRAPPED_FUNC(execv, int, (pathname, argv));
  return result;
}
int POSIX::execvp(const char *pathname, char *const argv[]) {
  BRAHMA_UNWRAPPED_FUNC(execvp, int, (pathname, argv));
  return result;
}
int POSIX::execvpe(const char *pathname, char *const argv[],
                   char *const envp[]) {
  BRAHMA_UNWRAPPED_FUNC(execvpe, int, (pathname, argv, envp));
  return result;
}

int POSIX::fork() {
  BRAHMA_UNWRAPPED_FUNC(fork, int, ());
  return result;
}

}  // namespace brahma