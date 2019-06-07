
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(/home/jwilloughby/projects/personal/chunklog/external)

add_library(${PROJECT_NAME} 
            buffered_logger.cpp
            # h5_logger.cpp
            h5_manager.cpp
            # chunk_logger.cpp
            chunk_manager.cpp)

target_link_libraries(${PROJECT_NAME} ${HDF5_LIBRARIES} chunklog)
