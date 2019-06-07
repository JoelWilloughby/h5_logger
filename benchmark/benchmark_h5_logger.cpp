#include <benchmark_utils.h>
#include <buffered_logger.h>

#include <benchmark/benchmark.h>

#include <vector>
#include <string>


static void BM_Test(benchmark::State& state) {
    std::vector<std::string> keys;
    std::vector<double> data;
    const uint32_t NUM_ELEMS = state.range(0);

    Logger::NormalLogger * logger = Logger::CreateLogger(Logger::H5_LOGGER);
    std::string filename = "bench.h5";

    state.counters["FileSize"] = 0;

    char buf[256];
    for(uint32_t i=0; i<state.range(1); i++) {
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

        state.PauseTiming();
        state.counters["FileSize"] = getFileSize(filename);
        state.ResumeTiming();
    }

    delete logger;
}

static void testArgs(benchmark::internal::Benchmark* b) {
        for(int j=64; j<=256; j*=2)
    for (int i = 0; i < 11; ++i)
            b->Args({8<<i,j});        
}

BENCHMARK(BM_Test)
    ->Apply(testArgs)
    ->Unit(benchmark::kMillisecond);