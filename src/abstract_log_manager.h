#ifndef ABSTRACT_LOG_MANAGER_H_
#define ABSTRACT_LOG_MANAGER_H_

#include <H5Cpp.h>

#include <string>
#include <vector>

namespace Logger {
    class AbstractLogManager {
    public:
        virtual bool open(const char * filename) = 0;
        virtual bool initialize(const std::vector<std::string>& keys, uint64_t startTime) = 0;
        virtual bool close() = 0;
        virtual bool isOpen() = 0;

        virtual bool writeData(double * data, uint64_t* times, size_t chunkSize, size_t currentChunk) = 0;
    };
}

#endif