include_directories(${CMAKE_CURRENT_SOURCE_DIR})


set(DEPENDENCIES ${PROJECT_NAME} gtest gtest_main pthread)
set(SOURCES 
    test_h5_logger.cpp
    test_ldf_logger.cpp
    h5_logger_fixture.cpp)
set(TEST_NAME ${PROJECT_NAME}-test)

add_executable(${TEST_NAME} ${SOURCES})
target_link_libraries(${TEST_NAME} ${DEPENDENCIES})

add_test(
    NAME ${TEST_NAME} 
    COMMAND ${TEST_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_custom_target(
    check 
    COMMAND ${CMAKE_CTEST_COMMAND}
    DEPENDS ${PROJECT_NAME} ${TEST_NAME})
