#ifndef ABSTRACT_LOGGER_H_
#define ABSTRACT_LOGGER_H_

#include <map>
#include <vector>

namespace Logger {
    template<typename Key, typename Value>
    class AbstractLogger {
    public:
        ~AbstractLogger() {}

        // Should start a log, given a set of keys, and an optional
        // context for log names, etc
        //
        // Return true on success of the log start, false otherwise
        virtual bool startLog(const std::vector<Key>& keys, const std::string& path) = 0;

        // Should stop a log.
        virtual bool stopLog() = 0;

        // Return true if the logger is currently logging
        virtual bool isLogging() = 0;

        // Sets the decimation in Herz
        virtual bool setDecimation(float decimationRateHz) = 0;

        // Logs some data with a key, value map
        virtual bool log(const std::map<Key, Value>& data) = 0;

        // Logs some data with a value vector. Understood that the keys have
        // Been passed in previously in start log
        virtual bool log(const std::vector<Value>& data) = 0;
    };
}

#endif