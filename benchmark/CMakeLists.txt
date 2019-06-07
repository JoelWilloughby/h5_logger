include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(BENCH_NAME_H5 ${PROJECT_NAME}-h5-bm)
set(BENCH_NAME_LDF ${PROJECT_NAME}-ldf-bm)

set(DEPENDENCIES ${PROJECT_NAME} benchmark benchmark_main pthread)

set(SOURCES 
    benchmark_h5_logger.cpp)

add_executable(${BENCH_NAME_H5} ${SOURCES})
target_link_libraries(${BENCH_NAME_H5} ${DEPENDENCIES})

set(SOURCES 
    benchmark_ldf_logger.cpp)

add_executable(${BENCH_NAME_LDF} ${SOURCES})
target_link_libraries(${BENCH_NAME_LDF} ${DEPENDENCIES})

