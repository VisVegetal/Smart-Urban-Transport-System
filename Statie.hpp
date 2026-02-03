#ifndef STATIE_HPP
#define STATIE_HPP

#include <string>
#include <vector>

class Statie {
private:
    std::strin nume;
    std::vector<std::string> rute;

public:
    explicit Statie(const std::string& nume);
    const std::string& getNume() const;
    void adaugaRuta(const std::string& numeRuta);
    void afiseaza() const;
};

#endif