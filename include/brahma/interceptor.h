//
// Created by hariharan on 8/8/22.
//

#ifndef BRAHMA_INTERCEPTOR_H
#define BRAHMA_INTERCEPTOR_H

#include <brahma/brahma_config.hpp>
/* Internal Headers */
#include <brahma/logging.h>
/* External Headers */
#include <gotcha/gotcha.h>

#include <cstdarg>
#include <memory>



// The unbinding points to the original function
#define GOTCHA_BINDING_MACRO(fname, CLASS)                            \
  if constexpr (!std::is_same_v<decltype(&C::fname),                  \
                                decltype(&CLASS::fname)>) {           \
    gotcha_binding_t binding = {#fname, (void*)fname##_wrapper,       \
                                &fname##_brahma_handle};              \
    bindings.push_back(binding);                                      \
    fname##_fptr fn = &::fname;                                     \
    if(fn){                                                 \
      gotcha_binding_t unbinding = {#fname, (void*)fn,      \
                                    &fname##_brahma_handle};          \
      unbindings.push_back(unbinding);                                \
      }                                                               \
}
#define GOTCHA_MACRO_TYPEDEF(macroname, macroret, macroargs, macro2args_val, macroclass_name)         \
  typedef macroret(*macroname##_fptr) macroargs;                                           \
  inline macroret macroname##_wrapper macroargs {                                          \
    return macroclass_name::get_instance()->macroname macro2args_val;                       \
  }                                                                         \
  macroret __attribute__((weak)) macroname macroargs;
#define GOTCHA_MACRO_TYPEDEF_OPEN(name, ret, args, args_val, start, \
                                  class_name)                       \
  typedef ret(*name##_fptr) args;                                   \
  inline ret name##_wrapper args {                                  \
    va_list _args;                                                  \
    va_start(_args, start);                                         \
    int mode = va_arg(_args, int);                                  \
    va_end(_args);                                                  \
    ret v = class_name::get_instance()->name args_val;              \
    return v;                                                       \
  }                                                                 \
  ret __attribute__((weak)) name args;

#define GOTCHA_MACRO_TYPEDEF_EXECL(name, ret, args, args_val, start, \
                                   class_name)                       \
  typedef ret(*name##_fptr) args;                                    \
  inline ret name##_wrapper args {                                   \
    va_list _args;                                                   \
    va_start(_args, start);                                          \
    char* val = va_arg(_args, char*);                                \
    va_end(_args);                                                   \
    ret v = class_name::get_instance()->name args_val;              \
    return v;                                                       \
  }                                                                 \
  ret __attribute__((weak)) name args; 

#define GOTCHA_MACRO_VAR(name) gotcha_wrappee_handle_t name##_brahma_handle;

#define BRAHMA_WRAPPER(name) name##_wrapper;

#define BRAHMA_UNWRAPPED_FUNC(macroname, ret, macroargs)                                \
  BRAHMA_LOG_INFO("[BRAHMA]\tFunction %s() not wrapped. Calling Original.\n", \
                  #macroname);                                                     \
  macroname##_fptr macroname##_wrappee =                                                \
      (macroname##_fptr)gotcha_get_wrappee(macroname##_brahma_handle);                  \
  ret result = macroname##_wrappee macroargs;

#define BRAHMA_UNWRAPPED_FUNC_VOID(macroname, macroargs)                                \
  BRAHMA_LOG_INFO("[BRAHMA]\tFunction %s() not wrapped. Calling Original.\n", \
                  #macroname);                                                     \
  macroname##_fptr macroname##_wrappee =                                                \
      (macroname##_fptr)gotcha_get_wrappee(macroname##_brahma_handle);                  \
  macroname##_wrappee macroargs;
#define BRAHMA_MAP_OR_FAIL(func_)                                      \
  auto __real_##func_ =                                                \
      (func_##_fptr)gotcha_get_wrappee(func_##_brahma_handle); \
  assert(__real_##func_ != NULL)

#endif  // BRAHMA_INTERCEPTOR_H
