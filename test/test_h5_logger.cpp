#include <gtest/gtest.h>
#include <h5_logger_fixture.h>
#include <h5_logger.h>

#include <cstdio>

using h5Test::H5LoggerTest;

TEST_F(H5LoggerTest, CreatesFile) {
    std::vector<std::string> keys;
    ASSERT_TRUE(logger->startLog(keys, filename));
    ASSERT_TRUE(logger->stopLog());

    FILE * f = fopen(filename.c_str(), "r");
    ASSERT_TRUE(f != NULL);
}

TEST_F(H5LoggerTest, ElementsStructure) {
    std::vector<std::string> keys;
    ASSERT_TRUE(logger->startLog(keys, filename));
    ASSERT_TRUE(logger->stopLog());

    ASSERT_EQ(hasGroup("/elements"), 0);
}

TEST_F(H5LoggerTest, KeysAsDataSets) {
    std::vector<std::string> keys;
    std::vector<double> data;

    char buf[256];
    for(unsigned i=0; i<10; i++) {
        sprintf(buf, "Key%u", i);
        keys.push_back(std::string(buf));
        data.push_back(i);
    }

    ASSERT_TRUE(logger->startLog(keys, filename));
    ASSERT_TRUE(logger->log(data));
    ASSERT_TRUE(logger->stopLog());

    for(auto key_it = keys.begin(); key_it != keys.end(); key_it++) {
        sprintf(buf, "/elements/%s", key_it->c_str());
        ASSERT_EQ(hasDataset(buf), 0);
    }
}

TEST_F(H5LoggerTest, SingleKeySingleChunk) {
    std::vector<std::string> keys;
    std::vector<double> data;
    const uint32_t NUM_ELEMS = 128;

    keys.push_back("Key");

    data.push_back(0);
    ASSERT_TRUE(logger->startLog(keys, filename));
    for(unsigned i=0; i<NUM_ELEMS; i++) {
        data[0] = i;
        ASSERT_TRUE(logger->log(data));
    }
    ASSERT_TRUE(logger->stopLog());

    int32_t numElems = numElementsInDataSet("elements/Key");
    ASSERT_EQ(numElems, NUM_ELEMS);
}

TEST_F(H5LoggerTest, SingleKeyMultiChunk) {
    std::vector<std::string> keys;
    std::vector<double> data;
    const uint32_t NUM_ELEMS = 1024;

    keys.push_back("Key");

    data.push_back(0);
    ASSERT_TRUE(logger->startLog(keys, filename));
    for(unsigned i=0; i<NUM_ELEMS; i++) {
        data[0] = i;
        ASSERT_TRUE(logger->log(data));
    }
    ASSERT_TRUE(logger->stopLog());

    int32_t numElems = numElementsInDataSet("elements/Key");
    ASSERT_EQ(numElems, NUM_ELEMS);
}

TEST_F(H5LoggerTest, MultiKeyMultiChunk) {
    std::vector<std::string> keys;
    std::vector<double> data;
    const uint32_t NUM_ELEMS = 1024;

    char buf[256];
    for(unsigned i=0; i<10; i++) {
        sprintf(buf, "Key%u", i);
        keys.push_back(std::string(buf));
        data.push_back(1000 * i + 1);
    }

    data.push_back(0);
    ASSERT_TRUE(logger->startLog(keys, filename));
    for(unsigned i=0; i<NUM_ELEMS; i++) {
        for(auto data_it = data.begin(); data_it != data.end(); data_it++) {
            *data_it /= 2.0;
        }

        ASSERT_TRUE(logger->log(data));
    }
    ASSERT_TRUE(logger->stopLog());

    for(auto key_iter = keys.begin(); key_iter != keys.end(); key_iter++) {
        sprintf(buf, "elements/%s", key_iter->c_str());
        int32_t numElems = numElementsInDataSet(buf);
        ASSERT_EQ(numElems, NUM_ELEMS);
    }
}

TEST_F(H5LoggerTest, MultiKeySingleChunk) {
    std::vector<std::string> keys;
    std::vector<double> data;
    const uint32_t NUM_ELEMS = 128;

    char buf[256];
    for(unsigned i=0; i<10; i++) {
        sprintf(buf, "Key%u", i);
        keys.push_back(std::string(buf));
        data.push_back(1000 * i + 1);
    }

    data.push_back(0);
    ASSERT_TRUE(logger->startLog(keys, filename));
    for(unsigned i=0; i<NUM_ELEMS; i++) {
        for(auto data_it = data.begin(); data_it != data.end(); data_it++) {
            *data_it /= 2.0;
        }

        ASSERT_TRUE(logger->log(data));
    }
    ASSERT_TRUE(logger->stopLog());

    for(auto key_iter = keys.begin(); key_iter != keys.end(); key_iter++) {
        sprintf(buf, "elements/%s", key_iter->c_str());
        int32_t numElems = numElementsInDataSet(buf);
        ASSERT_EQ(numElems, NUM_ELEMS);
    }
}

TEST_F(H5LoggerTest, BigLog) {
    std::vector<std::string> keys;
    std::vector<double> data;
    const uint32_t NUM_ELEMS = 40000;

    char buf[256];
    for(unsigned i=0; i<214; i++) {
        sprintf(buf, "Key%u", i);
        keys.push_back(std::string(buf));
        data.push_back(1000 * i + 1);
    }

    data.push_back(0);
    ASSERT_TRUE(logger->startLog(keys, filename));
    for(unsigned i=0; i<NUM_ELEMS; i++) {
        for(auto data_it = data.begin(); data_it != data.end(); data_it++) {
            *data_it += 2.0;
        }

        ASSERT_TRUE(logger->log(data));
    }
    ASSERT_TRUE(logger->stopLog());

    for(auto key_iter = keys.begin(); key_iter != keys.end(); key_iter++) {
        sprintf(buf, "elements/%s", key_iter->c_str());
        int32_t numElems = numElementsInDataSet(buf);
        ASSERT_EQ(numElems, NUM_ELEMS);
    }
}


