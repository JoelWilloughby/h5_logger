#include <benchmark/benchmark.h>
#include <h5_logger.h>

#include <vector>

static void BM_Test(benchmark::State& state) {
    std::vector<std::string> keys;
    std::vector<double> data;
    const uint32_t NUM_ELEMS = 40000;

    Logger::NormalLogger * logger = Logger::CreateLogger();
    std::string filename = "bench.h5";

    char buf[256];
    for(uint32_t i=0; i<214; i++) {
        sprintf(buf, "Key%u", i);
        keys.push_back(std::string(buf));
        data.push_back(1000 * i + 1);
    }

    unsigned count = 0;

    for(auto _ : state) {
        if(!logger->startLog(keys, filename)){
            state.SkipWithError("File failed to open");
            continue;
        };
        for(uint32_t i=0; i<NUM_ELEMS; i++) {
            for(auto data_it = data.begin(); data_it != data.end(); data_it++) {
                *data_it += 2.0;
            }

            logger->log(data);
        }
        logger->stopLog();
    }

    delete logger;
}

BENCHMARK(BM_Test);