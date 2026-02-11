#ifndef VEHICUL_FACTORY_HPP
#define VEHICUL_FACTORY_HPP

#include <memory>

#include "Vehicul.hpp"
#include "Autobuz.hpp"
#include "Tramvai.hpp"
#include "Metrou.hpp"
#include "Exceptii.hpp"

// Factory Method pentru crearea vehiculelor
class VehiculFactory {
public:
    static std::unique_ptr<Vehicul> creeazaVehicul(
        int tip,
        int id,
        int capacitate
    ) {
        switch (tip) {
            case 1:
                return std::make_unique<Autobuz>(id, capacitate);
            case 2:
                return std::make_unique<Tramvai>(id, capacitate);
            case 3:
                return std::make_unique<Metrou>(id, capacitate);
            default:
                throw TransportException("Tip vehicul invalid.");
        }
    }
};

#endif
