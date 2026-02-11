#ifndef EXCEPTII_HPP
#define EXCEPTII_HPP

#include <exception>
#include <string>

class TransportException : public std::exception {
protected:
    std::string mesaj;
public:
    explicit TransportException(std::string m) : mesaj(std::move(m)) {}
    [[nodiscard]] const char* what() const noexcept override { return mesaj.c_str(); }
};

class ValoareInvalidaException : public TransportException {
public:
    explicit ValoareInvalidaException(const std::string& m) : TransportException("Eroare Valoare: " + m) {}
};

class VehiculException : public TransportException {
public:
    explicit VehiculException(const std::string& m) : TransportException("Eroare Vehicul: " + m) {}
};

class RutaException : public TransportException {
public:
    explicit RutaException(const std::string& m) : TransportException("Eroare Ruta: " + m) {}
};

#endif