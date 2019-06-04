#include <h5_logger.h>

#include <H5Cpp.h>
#include <cstdio>
#include <filesystem>

namespace Logger {
    class H5Manager {
    public:
        H5Manager() : 
            h5file(nullptr)
        {
        }

        ~H5Manager() {
            close();
        }

        bool open(const char * filename) {
            if(h5file != nullptr) {
                return false;
            }

            h5file = new H5::H5File(filename, H5F_ACC_TRUNC);

            if(h5file == nullptr) {
                return false;
            }

            elements_group = h5file->createGroup("/elements");
            return true;
        }

        bool close() {
            if(h5file == nullptr) {
                return true;
            }

            elements_group.close();
            h5file->close();

            return true;
        }

        bool isOpen() {
            return h5file != nullptr;
        }

    private:
        H5::H5File* h5file;
        H5::Group elements_group;
    };

    H5Logger::H5Logger() {
        manager = new H5Manager();
    }

    H5Logger::~H5Logger() {
        delete manager;
    }
    
    // Should start a log, given a set of keys, and an optional
    // context for log names, etc
    //
    // Return true on success of the log start, false otherwise
    bool H5Logger::startLog(const std::vector<std::string>& keys, const std::string& path) {
        bool result = manager->open(path.c_str());
        return result;
    }

    // Should stop a log.
    bool H5Logger::stopLog() {
        bool result = manager->close();
        return result;
    }

    // Return true if the logger is currently logging
    bool H5Logger::isLogging() {
        return manager->isOpen();
    }

    // Sets the decimation in Herz
    bool H5Logger::setDecimation(float decimationRateHz) {
        return false;
    }

    // Logs some data with a key, value map
    bool H5Logger::log(const std::map<std::string, double>& data) {
        return false;
    }

    // Logs some data with a value vector. Understood that the keys have
    // Been passed in previously in start log
    bool H5Logger::log(const std::vector<double>& data) {
        return false;
    }
}