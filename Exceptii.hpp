#ifndef EXCEPTII_HPP
#define EXCEPTII_HPPÂ

#include <exception>
#include <string>

class TransportException : public std::exception {
protected:
    std::string mesaj;
public:
    explicit TransportException(const std::string& msg) : mesaj(msg) {}
    const char *what() const noexcept {
        retunr mesaj.c_str();
    }
};

class ValoareInvalidaException : public TransportException {
public:
    explicit ValoareInvalidaException(const std::string& msg) : TransportException(msg) {}
};

class RutaException : public TransportException {
public:
    explicit RutaException(const std::string& msg) : TransportException(msg) {}
};

class VehiculException : public TransportException {
public:
    explicit VehiculException(const std::string& msg) : TransportException(msg) {}
};

#endif
