//
// Created by hariharan on 8/16/22.
//
#include <brahma/interface/stdio.h>

namespace brahma {

std::shared_ptr<STDIO> STDIO::my_instance = nullptr;
FILE *STDIO::fopen(const char *path, const char *mode) {
  BRAHMA_UNWRAPPED_FUNC(fopen, FILE *, (path, mode));
  return result;
}

FILE *STDIO::fopen64(const char *path, const char *mode) {
  BRAHMA_UNWRAPPED_FUNC(fopen64, FILE *, (path, mode));
  return result;
}

int STDIO::fclose(FILE *fp) {
  BRAHMA_UNWRAPPED_FUNC(fclose, int, (fp));
  return result;
}

size_t STDIO::fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC(fread, size_t, (ptr, size, nmemb, stream));
  return result;
}

size_t STDIO::fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC(fwrite, size_t, (ptr, size, nmemb, stream));
  return result;
}

long STDIO::ftell(FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC(ftell, long, (stream));
  return result;
}

int STDIO::fseek(FILE *stream, long offset, int whence) {
  BRAHMA_UNWRAPPED_FUNC(fseek, int, (stream, offset, whence));
  return result;
}
FILE *STDIO::fdopen(int fd, const char *mode) {
  BRAHMA_UNWRAPPED_FUNC(fdopen, FILE *, (fd, mode));
  return result;
}
int STDIO::fileno(FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC(fileno, int, (stream));
  return result;
}
FILE *STDIO::tmpfile(void) {
  BRAHMA_UNWRAPPED_FUNC(tmpfile, FILE *, ());
  return result;
}
int STDIO::fseeko(FILE *stream, off_t offset, int whence) {
  BRAHMA_UNWRAPPED_FUNC(fseeko, int, (stream, offset, whence));
  return result;
}
off_t STDIO::ftello(FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC(ftello, off_t, (stream));
  return result;
}
}  // namespace brahma