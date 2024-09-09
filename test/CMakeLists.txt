
add_executable(test_posix_mpi test_posix_mpi.cpp)
add_dependencies(test_posix_mpi ${PROJECT_NAME})
target_link_libraries(test_posix_mpi ${PROJECT_NAME})
add_test(NAME test_posix_mpi COMMAND $<TARGET_FILE:test_posix_mpi>)

if(BRAHMA_BUILD_WITH_HDF5)
    add_executable(test_hdf5 test_hdf5.cpp)
    add_dependencies(test_hdf5 ${PROJECT_NAME})
    target_link_libraries(test_hdf5 ${PROJECT_NAME})
    add_test(NAME test_hdf5 COMMAND $<TARGET_FILE:test_hdf5>)
endif()
