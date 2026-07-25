//
// Created by hariharan.
//

#include <brahma/interface/stdio_bypass.h>
#include <dlfcn.h>

#include <cassert>

#ifndef BRAHMA_LIBC_SO_PATH
#define BRAHMA_LIBC_SO_PATH "libc.so.6"
#endif

namespace brahma {

STDIOBypass &STDIOBypass::get_instance() {
  static STDIOBypass instance;
  return instance;
}

void STDIOBypass::initialize() {
  if (initialized_) return;
  // libc is already loaded in every process; RTLD_NOLOAD means this just
  // returns a handle to the existing mapping, not a fresh load.
  void *libc = dlopen(BRAHMA_LIBC_SO_PATH, RTLD_LAZY | RTLD_NOLOAD);
  assert(libc != nullptr);
  real_vsnprintf_ = reinterpret_cast<vsnprintf_fn>(dlsym(libc, "vsnprintf"));
  assert(real_vsnprintf_ != nullptr);
  initialized_ = true;
}

int STDIOBypass::vsnprintf(char *str, size_t size, const char *format,
                           va_list args) {
  if (!initialized_) initialize();
  return real_vsnprintf_(str, size, format, args);
}

}  // namespace brahma
