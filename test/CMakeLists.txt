
set(TEST_BASIC_SRC test.cpp)
add_executable(test_basic ${TEST_BASIC_SRC})
add_dependencies(test_basic ${PROJECT_NAME})
target_link_libraries(test_basic ${PROJECT_NAME})

add_test(NAME basic_test COMMAND $<TARGET_FILE:test_basic>)