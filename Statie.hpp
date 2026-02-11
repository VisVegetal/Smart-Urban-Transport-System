#ifndef STATIE_HPP
#define STATIE_HPP

#include <string>
#include <vector>

class Statie {
private:
    std::string nume;  // numele statiei
    std::vector<std::string> rute;   // rutele asociate statiei

public:
    explicit Statie(const std::string& nume);

    [[nodiscard]] const std::string& getNume() const;
    void adaugaRuta(const std::string& numeRuta);
    void afiseaza() const;
};

#endif