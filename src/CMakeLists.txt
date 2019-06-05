
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} 
            h5_logger.cpp
            h5_manager.cpp)

target_link_libraries(${PROJECT_NAME} ${HDF5_LIBRARIES})
