#include <h5_logger_fixture.h>

namespace h5Test {
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
        logger = Logger::CreateLogger();
    }

    void H5LoggerTest::TearDown() {
        delete logger;
    }

    std::string H5LoggerTest::getFilename() {
        return std::string(::testing::UnitTest::GetInstance()->current_test_info()->name()) + ".h5";
    }

    int32_t H5LoggerTest::hasGroup(const char * groupPath) {
        char cmd[128];
        sprintf(cmd, "h5dump -g \"%s\" %s", groupPath, getFilename().c_str());
        return h5Test::exec(cmd, h5dumpres);
    }

    int32_t H5LoggerTest::hasDataset(const char * datasetPath) {
        char cmd[128];
        sprintf(cmd, "h5dump -d \"%s\" %s", datasetPath, getFilename().c_str());
        return h5Test::exec(cmd, h5dumpres);
    }

}