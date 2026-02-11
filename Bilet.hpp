#ifndef BILET_HPP
#define BILET_HPP

#include <string>

class Bilet {
protected:
    double pretBaza;
    std::string serie;

public:
    Bilet(double pret, std::string serie);
    virtual ~Bilet() = default;

    [[nodiscard]] virtual double getPretFinal() const = 0;
    [[nodiscard]] virtual std::string getDetalii() const;
    [[nodiscard]] std::string getSerie() const;
};

class BiletIntreg : public Bilet {
public:
    BiletIntreg(double pret, std::string serie);
    [[nodiscard]] double getPretFinal() const override;
};

class BiletRedus : public Bilet {
private:
    double procentReducere;
public:
    BiletRedus(double pret, std::string serie, double reducere);
    [[nodiscard]] double getPretFinal() const override;
};

#endif