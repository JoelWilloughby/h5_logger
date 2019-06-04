include_directories(${CMAKE_CURRENT_SOURCE_DIR})

macro(LOCAL_ADD_TEST testname testsource)
    add_executable(${testname} ${testsource})
    target_link_libraries(${testname} h5loggerstuff gtest gtest_main pthread)
    add_test(NAME ${testname} COMMAND ${testname})
endmacro(LOCAL_ADD_TEST)

LOCAL_ADD_TEST(test_h5_logger test_h5_logger.cpp)
