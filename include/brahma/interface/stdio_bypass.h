//
// Created by hariharan.
//

#ifndef BRAHMA_STDIO_BYPASS_H
#define BRAHMA_STDIO_BYPASS_H

#include <cstdarg>
#include <cstdio>

namespace brahma {

// Real libc vsnprintf, resolved once by initialize() via
// dlopen("libc.so.6", RTLD_NOLOAD) + dlsym(handle, "vsnprintf") -- NOT via
// gotcha_get_wrappee()/BRAHMA_UNWRAPPED_FUNC, and NOT via a plain global
// `vsnprintf(...)` call.
//
// Why: STDIO intercepts "vsnprintf" itself (it's one of the bound
// printf-family functions), so STDIO::snprintf()'s default passthrough
// calling the plain "vsnprintf" symbol -- or resolving it through
// gotcha_get_wrappee() -- routes back through GOTCHA's own PLT/GOT
// rewriting for that symbol, which depends on this library's own
// bind()/unbind() state and byte order of tool registration rather than
// always landing on true libc. dlopen()ing libc directly (RTLD_NOLOAD: it's
// already loaded in every process, this doesn't trigger a fresh load) and
// resolving the symbol from THAT library's own symbol table via dlsym()
// sidesteps GOTCHA's PLT/GOT entirely and is immune to bind()/unbind()
// state. Mirrors dftracer::STDIOBypass
// (dftracer/src/dftracer/core/utils/stdio_bypass.h) -- same mechanism, same
// rationale, scoped here to the one symbol brahma's own default
// implementations need it for.
class STDIOBypass {
 public:
  static STDIOBypass &get_instance();

  // Idempotent: only the first call actually resolves the symbol. dlopen/
  // dlsym are not async-signal-safe, so callers that might need this from a
  // signal-handler context should call it ahead of time; brahma's own use
  // (STDIO::snprintf's default implementation) calls it lazily on first use,
  // which is safe since that call path is never invoked from a signal
  // handler here.
  void initialize();

  int vsnprintf(char *str, size_t size, const char *format, va_list args);

 private:
  STDIOBypass() = default;
  STDIOBypass(const STDIOBypass &) = delete;
  STDIOBypass &operator=(const STDIOBypass &) = delete;

  bool initialized_ = false;

  using vsnprintf_fn = int (*)(char *, size_t, const char *, va_list);
  vsnprintf_fn real_vsnprintf_ = nullptr;
};

}  // namespace brahma

#endif  // BRAHMA_STDIO_BYPASS_H
