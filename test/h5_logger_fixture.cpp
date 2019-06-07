#include <h5_logger_fixture.h>

#include <H5Cpp.h>

namespace LoggerTest {
    int32_t exec(const char* cmd, std::string& output) {
        char buffer[128];
        FILE* pipe = popen(cmd, "r");
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }

        try {
            while (fgets(buffer, sizeof buffer, pipe) != NULL) {
                output += buffer;
            }
        } catch (...) {
            pclose(pipe);
            throw;
        }
        int32_t result = pclose(pipe);
        return result;
    }

    void H5LoggerTest::SetUp() {
        filename = getFilename();
        logger = Logger::CreateLogger(Logger::H5_LOGGER);
    }

    void H5LoggerTest::TearDown() {
        delete logger;
    }

    std::string H5LoggerTest::getFilename() {
        return std::string(::testing::UnitTest::GetInstance()->current_test_info()->name()) + ".h5";
    }

    int32_t H5LoggerTest::hasGroup(const char * groupPath) {
        char cmd[128];
        sprintf(cmd, "h5dump -g \"%s\" %s", groupPath, filename.c_str());
        return LoggerTest::exec(cmd, h5dumpres);
    }

    int32_t H5LoggerTest::hasDataset(const char * datasetPath) {
        char cmd[128];
        sprintf(cmd, "h5dump -d \"%s\" %s", datasetPath, filename.c_str());
        return LoggerTest::exec(cmd, h5dumpres);
    }

    int32_t H5LoggerTest::numElementsInDataSet(const char * datasetPath) {

        int32_t result = -1;

        try {
            H5::H5File h5file(filename.c_str(), H5F_ACC_RDONLY);
            H5::DataSet dataset = h5file.openDataSet(datasetPath);
            result = dataset.getSpace().getSelectNpoints();
            h5file.close();
        }
        catch(...) {

        }

        return result;
    }

}