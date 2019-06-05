#ifndef H5_MANAGER_H_
#define H5_MANAGER_H_

#include <H5Cpp.h>

#include <string>
#include <vector>

namespace Logger {
    class H5Manager {
    public:
        H5Manager();
        ~H5Manager();

        bool open(const char * filename);
        bool initialize(const std::vector<std::string>& keys, hsize_t chunkSize);
        bool close();
        bool isOpen();

        bool writeData(double * data, hsize_t chunkSize, hsize_t currentChunk);

    private:
        H5::H5File* h5file;
        H5::Group elements_group;
        std::vector<H5::DataSet> datasets;
    };
}

#endif