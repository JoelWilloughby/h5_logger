#include <gtest/gtest.h>
#include <h5_logger.h>

#include <string>

namespace h5Test {

    class H5LoggerTest : public ::testing::Test {
    protected:
        Logger::NormalLogger* logger;
        std::string h5dumpres;
        std::string filename;

        void SetUp();

        void TearDown();

        int32_t hasGroup(const char * groupPath);

        int32_t hasDataset(const char * datasetPath);

        int32_t numElementsInDataSet(const char * datasetPath);

    private:
        std::string getFilename();
    };
}

