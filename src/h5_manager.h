#ifndef H5_MANAGER_H_
#define H5_MANAGER_H_

#include <abstract_log_manager.h>
#include <H5Cpp.h>

#include <string>
#include <vector>

namespace Logger {
    class H5Manager : public AbstractLogManager{
    public:
        H5Manager();
        ~H5Manager();

        bool open(const char * filename);
        bool initialize(const std::vector<std::string>& keys, uint64_t startTime);
        bool close();
        bool isOpen();

        bool writeData(double * data, uint64_t * times, size_t chunkSize, size_t currentChunk);

    private:
        void makeDatasets(hsize_t chunkSize);

        H5::H5File* h5file;
        H5::Group elements_group;
        std::vector<H5::DataSet> datasets;
        std::vector<std::string> keys;
    };
}

#endif