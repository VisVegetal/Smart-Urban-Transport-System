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
    static Logger* instance;                 // instanta unica
    std::vector<std::string> logs;           // loguri interne

    Logger() = default;                      // constructor privat
    Logger(const Logger&) = delete;          // fara copiere
    Logger& operator=(const Logger&) = delete;

    static std::string levelToString(LogLevel level);

public:
    static Logger& getInstance();             // acces la instanta unica

    void log(LogLevel level, const std::string& mesaj);
    void afiseazaLoguri() const;
    void salveazaInFisier(const std::string& numeFisier) const;
};

#endif
