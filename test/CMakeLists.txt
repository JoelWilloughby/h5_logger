macro(LOCAL_ADD_TEST testname testsource)
    add_executable(${testname} ${testsource})
    target_link_libraries(${testname} gtest gtest_main pthread)
    add_test(NAME ${testname} COMMAND ${testname})
endmacro(LOCAL_ADD_TEST)

LOCAL_ADD_TEST(testit testit.cpp)
