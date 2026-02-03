#include <iostream>

#include "Dispecerat.hpp"
#include "Autobuz.hpp"
#include "Tramvai.hpp"
#include "Metrou.hpp"
#include "Ruta.hpp"
#include "Exceptii.hpp"

int main() {
    try {
        std::cout << "=== Smart Urban Transport System ===\n\n";

        Ruta ruta1("Ruta Centrala", 12.5);

        Dispecerat dispecerat;

        Autobuz a1(1, 50);
        Tramvai t1(2, 120);
        Metrou m1(3, 300);

        dispecerat.adaugaVehicul(a1);
        dispecerat.adaugaVehicul(t1);
        dispecerat.adaugaVehicul(m1);

        std::cout << "Vehicule active:\n";
        dispecerat.afiseazaVehicule();

        double timp = dispecerat.calculeazaTimpTotal(ruta1);

        std::cout << "\nTimp total estimat pe "
                  << ruta1.getNume()
                  << ": " << timp << " ore\n";

        std::cout << "\nNumar total vehicule create: "
                  << Vehicul::getNumarVehicule()
                  << "\n";
    }
    catch (const TransportException& e) {
        std::cerr << "Eroare de transport: " << e.what() << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Eroare standard: " << e.what() << "\n";
    }

    return 0;
}
