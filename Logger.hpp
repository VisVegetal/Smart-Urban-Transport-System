#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <vector>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

class Logger {
private:
    static std::vector<std::string> logs;

    static std::string levelToString(LogLevel level);

public:
    static void log(LogLevel level, const std::string& mesaj);
    static void afiseazaLoguri();
    static void salveazaInFisier(const std::string& numeFisier);
};

#endif // LOGGER_HPP
