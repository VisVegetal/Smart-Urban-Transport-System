#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <vector>

enum class LogLevel { INFO, WARNING, ERROR };

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void log(LogLevel level, const std::string& message) {
        std::string prefix;
        switch (level) {
            case LogLevel::INFO: prefix = "[INFO] "; break;
            case LogLevel::WARNING: prefix = "[WARN] "; break;
            case LogLevel::ERROR: prefix = "[ERROR] "; break;
        }
        logs.push_back(prefix + message);
        std::cout << prefix << message << "\n";
    }

    void showLogs() const;
    void saveToFile(const std::string& fileName) const;

private:
    Logger() = default;
    ~Logger() = default;
    std::vector<std::string> logs;
};

#endif
