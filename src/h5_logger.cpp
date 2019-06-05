#include <h5_logger.h>
#include <h5_manager.h>

#include <cstdio>
#include <cstring>

namespace Logger {

    class H5Logger : public NormalLogger {
    public:
        H5Logger() {
            manager = new H5Manager();
        }

        ~H5Logger() {
            delete manager;
        }

        bool startLog(const std::vector<std::string>& keys, const std::string& path) {
            bool result = manager->open(path.c_str());
            if(!result) {
                return false;
            }

            manager->initialize(keys);

            dataBuffer = new double[keys.size() * CHUNK_SIZE + 1];
            chunkOffset = 0;
            currentChunk = 0;
            numKeys = keys.size();

            return result;
        }

        bool stopLog() {
            // Clean up
            writeChunk();

            delete [] dataBuffer;

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

            manager->writeData(dataBuffer, chunkOffset, currentChunk * CHUNK_SIZE);

            currentChunk++;
            chunkOffset = 0;
        }


        hsize_t CHUNK_SIZE = 128;
        H5Manager * manager;

        double * dataBuffer;
        uint32_t chunkOffset;
        uint32_t currentChunk;
        uint32_t numKeys;
    };

    NormalLogger * CreateLogger(){
        return new H5Logger();
    }
}