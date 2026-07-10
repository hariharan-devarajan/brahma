# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/usr/workspace/haridev/dftracer-project/brahma/build_verify/_deps/gotcha-src"
  "/usr/workspace/haridev/dftracer-project/brahma/build_verify/_deps/gotcha-build"
  "/usr/WS2/haridev/dftracer-project/brahma/build_verify/_deps/gotcha-subbuild/gotcha-populate-prefix"
  "/usr/WS2/haridev/dftracer-project/brahma/build_verify/_deps/gotcha-subbuild/gotcha-populate-prefix/tmp"
  "/usr/WS2/haridev/dftracer-project/brahma/build_verify/_deps/gotcha-subbuild/gotcha-populate-prefix/src/gotcha-populate-stamp"
  "/usr/WS2/haridev/dftracer-project/brahma/build_verify/_deps/gotcha-subbuild/gotcha-populate-prefix/src"
  "/usr/WS2/haridev/dftracer-project/brahma/build_verify/_deps/gotcha-subbuild/gotcha-populate-prefix/src/gotcha-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/usr/WS2/haridev/dftracer-project/brahma/build_verify/_deps/gotcha-subbuild/gotcha-populate-prefix/src/gotcha-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/usr/WS2/haridev/dftracer-project/brahma/build_verify/_deps/gotcha-subbuild/gotcha-populate-prefix/src/gotcha-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
