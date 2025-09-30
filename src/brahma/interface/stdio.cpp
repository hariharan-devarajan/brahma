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


void STDIO::clearerr(FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC_VOID(clearerr, (stream));
}
int STDIO::feof(FILE * stream) {
    BRAHMA_UNWRAPPED_FUNC(feof, int, (stream));
    return result;
}
int STDIO::ferror(FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC(ferror, int, (stream));
  return result;
}
int STDIO::fflush(FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC(fflush, int, (stream));
  return result;
}
int STDIO::fgetc(FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC(fgetc, int, (stream));
  return result;
}
int STDIO::fgetpos(FILE *stream, fpos_t *pos) {
  BRAHMA_UNWRAPPED_FUNC(fgetpos, int, (stream, pos));
  return result;
}
char* STDIO::fgets(char *s, int size, FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC(fgets, char*, (s, size, stream));
  return result;
}
void STDIO::flockfile(FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC_VOID(flockfile, (stream));
}
int STDIO::fputc(int c, FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC(fputc, int, (c, stream));
  return result;
}
int STDIO::fputs(const char *s, FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC(fputs, int, (s, stream));
  return result;
}
  FILE* STDIO::freopen(const char *pathname, const char *mode, FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC(freopen, FILE*, (pathname, mode, stream));
  return result;
}
int STDIO::fsetpos(FILE *stream, const fpos_t *pos) {
  BRAHMA_UNWRAPPED_FUNC(fsetpos, int, (stream, pos));
  return result;
}
int STDIO::ftrylockfile(FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC(ftrylockfile, int, (stream));
  return result;
}
void STDIO::funlockfile(FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC_VOID(funlockfile, (stream));
}
int STDIO::getc(FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC(getc, int, (stream));
  return result;
}
int STDIO::getc_unlocked(FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC(getc_unlocked, int, (stream));
  return result;
}
int STDIO::getw(FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC(getw, int, (stream));
  return result;
}
int STDIO::pclose(FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC(pclose, int, (stream));
  return result;
}
int STDIO::putw(int w, FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC(putw, int, (w, stream));
  return result;
}
void STDIO::rewind(FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC_VOID(rewind, (stream));
}
int STDIO::setvbuf(FILE *stream, char *buf, int mode, size_t size) {
  BRAHMA_UNWRAPPED_FUNC(setvbuf, int, (stream, buf, mode, size));
  return result;
}
int STDIO::ungetc(int c, FILE *stream) {
  BRAHMA_UNWRAPPED_FUNC(ungetc, int, (c, stream));
  return result;
}


size_t brahma::STDIO::unbind() {
  num_bindings = unbindings.size();
  if (num_bindings > 0) {
    gotcha_binding_t *raw_bindings = unbindings.data();
    char unbind_name[128];
    sprintf(unbind_name, "%s_stdio_unbind", tool_name);
    gotcha_wrap(raw_bindings, num_bindings, unbind_name);
    gotcha_set_priority(unbind_name, bind_priority+1);
  }
  return num_bindings;
}
}  // namespace brahma