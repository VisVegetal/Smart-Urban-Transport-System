#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <vector>
#include <string>

enum class LogLevel { INFO, WARNING, ERROR };

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void log(LogLevel level, const std::string& mesaj) {
        std::string prefix;
        switch (level) {
            case LogLevel::INFO: prefix = "[INFO] "; break;
            case LogLevel::WARNING: prefix = "[WARN] "; break;
            case LogLevel::ERROR: prefix = "[ERR ] "; break;
        }
        loguri.push_back(prefix + mesaj);
        std::cout << prefix << mesaj << std::endl;
    }

    void afiseazaLoguri() const;
    void salveazaInFisier(const std::string& numeFisier) const;

private:
    Logger() = default;
    ~Logger() = default;
    std::vector<std::string> loguri;
};

#endif