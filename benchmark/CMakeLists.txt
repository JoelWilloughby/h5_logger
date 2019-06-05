include_directories(${CMAKE_CURRENT_SOURCE_DIR})

link_directories(~/projects/google/benchmark/build/src)
include_directories(~/projects/google/benchmark/include)

set(DEPENDENCIES ${PROJECT_NAME} benchmark benchmark_main pthread)
set(SOURCES 
    benchmark_h5_logger.cpp)
set(BENCH_NAME ${PROJECT_NAME}-bm)

add_executable(${BENCH_NAME} ${SOURCES})
target_link_libraries(${BENCH_NAME} ${DEPENDENCIES})

add_test(
    NAME ${BENCH_NAME} 
    COMMAND ${BENCH_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
