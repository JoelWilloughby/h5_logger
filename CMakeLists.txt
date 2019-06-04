cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(h5logger VERSION 0.1.0 LANGUAGES CXX C)
enable_testing()

find_package(HDF5 REQUIRED)
include_directories(${HDF5_INCLUDE_DIR})

include_directories(include)

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(test)

