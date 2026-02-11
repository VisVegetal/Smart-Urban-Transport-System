#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <vector>

// niveluri de severitate ale mesajelor de log
enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

class Logger {
private:
    static Logger* instance;
    std::vector<std::string> logs;

    Logger() = default;
    static std::string levelToString(LogLevel level);

public:
    static Logger& getInstance();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void log(LogLevel level, const std::string& mesaj);
    void afiseazaLoguri() const;
    void salveazaInFisier(const std::string& numeFisier) const;
};

#endif
