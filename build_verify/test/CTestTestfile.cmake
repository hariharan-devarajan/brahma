# CMake generated Testfile for 
# Source directory: /usr/workspace/haridev/dftracer-project/brahma/test
# Build directory: /usr/workspace/haridev/dftracer-project/brahma/build_verify/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_posix "/usr/workspace/haridev/dftracer-project/brahma/build_verify/bin/test_posix")
set_tests_properties(test_posix PROPERTIES  _BACKTRACE_TRIPLES "/usr/workspace/haridev/dftracer-project/brahma/test/CMakeLists.txt;5;add_test;/usr/workspace/haridev/dftracer-project/brahma/test/CMakeLists.txt;0;")
add_test(test_mpiio "/usr/workspace/haridev/dftracer-project/brahma/build_verify/bin/test_mpiio")
set_tests_properties(test_mpiio PROPERTIES  _BACKTRACE_TRIPLES "/usr/workspace/haridev/dftracer-project/brahma/test/CMakeLists.txt;11;add_test;/usr/workspace/haridev/dftracer-project/brahma/test/CMakeLists.txt;0;")
add_test(test_mpi "/usr/workspace/haridev/dftracer-project/brahma/build_verify/bin/test_mpi")
set_tests_properties(test_mpi PROPERTIES  _BACKTRACE_TRIPLES "/usr/workspace/haridev/dftracer-project/brahma/test/CMakeLists.txt;15;add_test;/usr/workspace/haridev/dftracer-project/brahma/test/CMakeLists.txt;0;")
add_test(test_hdf5 "/usr/workspace/haridev/dftracer-project/brahma/build_verify/bin/test_hdf5")
set_tests_properties(test_hdf5 PROPERTIES  _BACKTRACE_TRIPLES "/usr/workspace/haridev/dftracer-project/brahma/test/CMakeLists.txt;22;add_test;/usr/workspace/haridev/dftracer-project/brahma/test/CMakeLists.txt;0;")
