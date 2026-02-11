#include "Ruta.hpp"
#include <utility>

Ruta::Ruta(std::string nume, double distanta)
    : nume(std::move(nume)), distanta(distanta) {
}