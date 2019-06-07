#include <buffered_logger.h>
#include <h5_manager.h>
#include <chunk_manager.h>

#include <chrono>
#include <cstdio>
#include <cstring>

namespace Logger {

    uint64_t timeNanos() {
        auto nowish = std::chrono::system_clock::now();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(nowish.time_since_epoch()).count();
    }

    class BufferedLogger : public NormalLogger {
    public:
        BufferedLogger(LoggerType loggerType) : dataBuffer(nullptr) {
            if(loggerType == H5_LOGGER) {
                this->manager = new H5Manager();
            }
            else if(loggerType == LDF_LOGGER) {
                this->manager = new ChunkManager();
            }
        }

        ~BufferedLogger() {
            delete manager;
        }

        bool startLog(const std::vector<std::string>& keys, const std::string& path) {
            bool result = manager->open(path.c_str());
            if(!result) {
                return false;
            }

            manager->initialize(keys,timeNanos());

            dataBuffer = new double[keys.size() * CHUNK_SIZE + 1];
            timeBuffer = new uint64_t[CHUNK_SIZE + 1];
            chunkOffset = 0;
            currentChunk = 0;
            numKeys = keys.size();

            return result;
        }

        bool stopLog() {
            // Clean up
            writeChunk();

            if(dataBuffer != nullptr) {
                delete [] dataBuffer;
                dataBuffer = nullptr;
            }
            if(timeBuffer != nullptr) {
                delete [] timeBuffer;
                timeBuffer = nullptr;
            }

            bool result = manager->close();

            return result;
        }

        bool isLogging() {
            return manager->isOpen();
        }

        bool setDecimation(float decimationRateHz) {
            return false;
        }

        bool log(const std::map<std::string, double>& data) {
            return false;
        }

        bool log(const std::vector<double>& data) {
            auto start = dataBuffer + chunkOffset*numKeys;
            size_t length = numKeys * sizeof(double);
            memcpy(start, data.data(), length);

            timeBuffer[chunkOffset] = timeNanos();

            chunkOffset++;

            if(chunkOffset == CHUNK_SIZE) {
                // Buffer is now full, write it
                writeChunk();
            }

            return true;
        }

    private:
        void writeChunk() {
            if(chunkOffset == 0) {
                // Nothing to do here
                return;
            }

            manager->writeData(dataBuffer, timeBuffer,  chunkOffset, currentChunk * CHUNK_SIZE);

            currentChunk++;
            chunkOffset = 0;
        }


        size_t CHUNK_SIZE = 128;
        AbstractLogManager * manager;

        double * dataBuffer;
        uint64_t * timeBuffer;
        uint32_t chunkOffset;
        uint32_t currentChunk;
        uint32_t numKeys;
    };

    NormalLogger * CreateLogger(LoggerType loggerType){
        return new BufferedLogger(loggerType);
    }
}