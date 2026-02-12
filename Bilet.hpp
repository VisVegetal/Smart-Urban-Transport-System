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

    // Metoda pura (clasa devine abstracta)
    [[nodiscard]] virtual Bilet* clone() const = 0;

    [[nodiscard]] virtual double getPretFinal() const = 0;
    [[nodiscard]] virtual std::string getDetalii() const;
    [[nodiscard]] const std::string getSerie() const;
};

class BiletIntreg : public Bilet {
public:
    BiletIntreg(double pret, std::string serie);
    [[nodiscard]] double getPretFinal() const override;

    // IMPLEMENTAREA LUI CLONE (Asta lipsea)
    [[nodiscard]] Bilet* clone() const override {
        return new BiletIntreg(*this);
    }
};

class BiletRedus : public Bilet {
private:
    double procentReducere;
public:
    BiletRedus(double pret, std::string serie, double reducere);
    [[nodiscard]] double getPretFinal() const override;

    [[nodiscard]] Bilet* clone() const override {
        return new BiletRedus(*this);
    }
};

#endif