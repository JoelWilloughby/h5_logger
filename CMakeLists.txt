cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(h5logger VERSION 0.1.0 LANGUAGES CXX C)


find_package(HDF5 REQUIRED)
include_directories(${HDF5_INCLUDE_DIR})

include_directories(include)
include_directories(SYSTEM hdf5/serial)

add_subdirectory(src)
add_subdirectory(examples)
