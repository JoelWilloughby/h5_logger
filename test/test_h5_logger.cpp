#include <gtest/gtest.h>
#include <h5_logger_fixture.h>
#include <h5_logger.h>

#include <cstdio>

using Logger::H5Logger;
using h5Test::H5LoggerFixture;

TEST_F(H5LoggerFixture, CreatesFile) {
    std::vector<std::string> keys;
    std::string filename = getFilename();
    ASSERT_TRUE(logger.startLog(keys, filename));
    ASSERT_TRUE(logger.stopLog());

    FILE * f = fopen(filename.c_str(), "r");
    ASSERT_TRUE(f != NULL);
}

TEST_F(H5LoggerFixture, ElementsStructure) {
    std::vector<std::string> keys;
    std::string filename = getFilename();
    ASSERT_TRUE(logger.startLog(keys, filename));
    ASSERT_TRUE(logger.stopLog());

    ASSERT_EQ(hasGroup("/elements"), 0);
}

TEST_F(H5LoggerFixture, KeysAsDataSets) {
    std::vector<std::string> keys;
    char buf[256];
    for(unsigned i=0; i<10; i++) {
        sprintf(buf, "Key%u", i);
        keys.push_back(std::string(buf));
    }

    std::string filename = getFilename();
    ASSERT_TRUE(logger.startLog(keys, filename));
    ASSERT_TRUE(logger.stopLog());

    for(auto key_it = keys.begin(); key_it != keys.end(); key_it++) {
        sprintf(buf, "/elements/%s", key_it->c_str());
        ASSERT_EQ(hasDataset(buf), 0);
    }
}
