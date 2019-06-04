#include <gtest/gtest.h>
#include <h5_logger.h>

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

    class H5LoggerFixture : public ::testing::Test {
    protected:
        Logger::H5Logger logger;
        std::string h5dumpres;

        void SetUp() {
        }

        void TearDown() {
        }

        std::string getFilename() {
            return "./" + std::string(::testing::UnitTest::GetInstance()->current_test_info()->name()) + ".h5";
        }

        int32_t hasGroup(const char * groupPath) {
            char cmd[128];
            sprintf(cmd, "h5dump -g \"%s\" %s", groupPath, getFilename().c_str());
            return h5Test::exec(cmd, h5dumpres);
        }

        int32_t hasDataset(const char * datasetPath) {
            char cmd[128];
            sprintf(cmd, "h5dump -d \"%s\" %s", datasetPath, getFilename().c_str());
            return h5Test::exec(cmd, h5dumpres);
        }
    };
}

