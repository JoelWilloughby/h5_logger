
add_library(h5loggerstuff 
            h5_logger.cpp)

target_link_libraries(h5loggerstuff ${HDF5_LIBRARIES})