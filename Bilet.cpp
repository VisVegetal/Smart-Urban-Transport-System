#include "Bilet.hpp"

#include <utility>

Bilet::Bilet(double pret, std::string serie) : pretBaza(pret), serie(std::move(serie)) {}
const std::string Bilet::getSerie() const { return serie; }
std::string Bilet::getDetalii() const { return "Serie: " + serie; }

BiletIntreg::BiletIntreg(double pret, std::string serie) : Bilet(pret, std::move(serie)) {}
double BiletIntreg::getPretFinal() const { return pretBaza; }

BiletRedus::BiletRedus(double pret, std::string serie, double reducere) 
    : Bilet(pret, std::move(serie)), procentReducere(reducere) {}
double BiletRedus::getPretFinal() const { return pretBaza * (1.0 - procentReducere); }