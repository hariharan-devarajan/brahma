
add_executable(test_posix test_posix.cpp)
add_dependencies(test_posix ${PROJECT_NAME})
target_link_libraries(test_posix ${PROJECT_NAME})
add_test(NAME test_posix COMMAND $<TARGET_FILE:test_posix>)

if(BRAHMA_BUILD_WITH_MPI)
    add_executable(test_mpi test_mpiio.cpp)
    add_dependencies(test_mpi ${PROJECT_NAME})
    target_link_libraries(test_mpi ${PROJECT_NAME})
    add_test(NAME test_mpi COMMAND $<TARGET_FILE:test_mpi>)
endif()

if(BRAHMA_BUILD_WITH_HDF5)
    add_executable(test_hdf5 test_hdf5.cpp)
    add_dependencies(test_hdf5 ${PROJECT_NAME})
    target_link_libraries(test_hdf5 ${PROJECT_NAME})
    add_test(NAME test_hdf5 COMMAND $<TARGET_FILE:test_hdf5>)
endif()
