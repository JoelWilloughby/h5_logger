#ifndef BENCHMARK_UTILS_H_
#define BENCHMARK_UTILS_H_

#include <string>
#include <sys/stat.h>

long getFileSize(const std::string& filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

#endif