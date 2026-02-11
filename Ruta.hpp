#ifndef RUTA_HPP
#define RUTA_HPP

#include <string>
#include <iostream>

class Ruta {
private:
    std::string nume;
    double distanta;

public:
    Ruta();
    Ruta(const std::string& nume, double distanta);
    Ruta(const Ruta& other);

    Ruta& operator=(const Ruta& other);
    ~Ruta() = default;

    [[nodiscard]] const std::string& getNume() const;
    [[nodiscard]] double getDistanta() const;

    void setNume(const std::string& numeNou);
    void setDistanta(double distantaNoua);

    bool operator==(const Ruta& other) const;
    bool operator!=(const Ruta& other) const;
    bool operator<(const Ruta& other) const;
    bool operator>(const Ruta& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Ruta& r);
};

#endif