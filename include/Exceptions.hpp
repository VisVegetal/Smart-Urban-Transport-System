#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>
#include <utility>

class TransportException : public std::exception {
protected:
    std::string message;

public:
    explicit TransportException(std::string m) : message(std::move(m)) {}
    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }
};

class InvalidValueException : public TransportException {
public:
    explicit InvalidValueException(const std::string& m)
        : TransportException("Value Error: " + m) {}
};

class VehicleException : public TransportException {
public:
    explicit VehicleException(const std::string& m)
        : TransportException("Vehicle Error: " + m) {}
};

class RouteException : public TransportException {
public:
    explicit RouteException(const std::string& m)
        : TransportException("Route Error: " + m) {}
};

#endif
