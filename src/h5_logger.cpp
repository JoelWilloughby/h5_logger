#include <h5_logger.h>

#include <H5Cpp.h>
#include <cstdio>
#include <filesystem>

namespace Logger {
    class H5Manager {
    public:
        H5Manager() : 
            fd(-1)
        {
        }

        ~H5Manager() {
            close();
        }

        bool open(const char * filename) {
            if(fd >= 0) {
                return false;
            }

            fd = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
            elements_id = H5Gcreate(fd, "/elements", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

            return isOpen();
        }

        bool close() {
            if(fd < 0) {
                return true;
            }

            H5Gclose(elements_id);
            herr_t status = H5Fclose(fd);
            fd = -1;
            return status >= 0;
        }

        bool isOpen() {
            return fd >= 0;
        }

    private:
        hid_t fd;
        hid_t elements_id;
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