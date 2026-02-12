#include "Ticketing.hpp"
#include <iostream>

SistemTicketing::SistemTicketing() : venitTotal(0.0), contorSerie(1000) {}

SistemTicketing::SistemTicketing(const SistemTicketing& other) {
    this->venitTotal = other.venitTotal;
    this->contorSerie = other.contorSerie;
    this->bileteVandute.clear();
    for (const auto& b : other.bileteVandute) {
        if (b) {
            this->bileteVandute.push_back(std::unique_ptr<Bilet>(b->clone()));
        }
    }
}

SistemTicketing& SistemTicketing::operator=(const SistemTicketing& other) {
    if (this != &other) {
        this->venitTotal = other.venitTotal;
        this->contorSerie = other.contorSerie;
        this->bileteVandute.clear();
        for (const auto& b : other.bileteVandute) {
            if (b) {
                this->bileteVandute.push_back(std::unique_ptr<Bilet>(b->clone()));
            }
        }
    }
    return *this;
}

void SistemTicketing::emiteBiletIntreg(double pret) {
    std::string serie = "INT-" + std::to_string(++contorSerie);
    bileteVandute.push_back(std::make_unique<BiletIntreg>(pret, serie));
}

void SistemTicketing::emiteBiletRedus(double pret, double reducere) {
    std::string serie = "RED-" + std::to_string(++contorSerie);
    bileteVandute.push_back(std::make_unique<BiletRedus>(pret, serie, reducere));
}

double SistemTicketing::calculeazaVenituri() const {
    double total = 0;
    for (const auto& b : bileteVandute) {
        total += b->getPretFinal();
    }
    return total;
}

void SistemTicketing::afiseazaIstoric() const {
    std::cout << "--- ISTORIC VANZARI BILETE ---\n";
    for (const auto& b : bileteVandute) {
        std::cout << b->getDetalii() << " | Pret: " << b->getPretFinal() << " RON\n";
    }
}

void SistemTicketing::anuleazaUltimulBilet() {
    if (!bileteVandute.empty()) bileteVandute.pop_back();
}

void SistemTicketing::curataIstoric() {
    bileteVandute.clear();
}