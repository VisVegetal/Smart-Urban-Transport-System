#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <vector>

#include "Dispecerat.hpp"
#include "Vehicul.hpp"
#include "Exceptii.hpp"
#include "Logger.hpp"
#include "Persistenta.hpp"
#include "Statistici.hpp"
#include "VehiculFactory.hpp"
#include "Mentenanta.hpp"
#include "Statistica.hpp"
#include "Incident.hpp"

void curataInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void afiseazaMeniu() {
    std::cout << "\n=== SISTEM GESTIUNE TRANSPORT URBAN ===\n";
    std::cout << "1. Adauga Vehicul | 2. Sterge Vehicul | 3. Afiseaza Vehicule\n";
    std::cout << "4. Adauga Ruta | 5. Afiseaza Rute | 16. Sterge Ruta\n";
    std::cout << "6. Adauga Incident | 7. Afiseaza Incidente | 8. Timp Total Traseu\n";
    std::cout << "9. Afiseaza Loguri | 10. Salveaza Loguri | 11. Simuleaza Cursa\n";
    std::cout << "12. Salveaza Sistem | 13. Incarca Sistem | 17. Valideaza Fisier\n";
    std::cout << "14. Raport Detaliat | 15. Distributie Tipuri | 18. Export Statistici\n";
    std::cout << "19. Cel mai rapid vehicul | 20. Capacitate Maxima | 21. Timp Mediu Ruta\n";
    std::cout << "22. Raport General | 23. Venituri Totale | 24. Recomandare Smart\n";
    std::cout << "25. Trimite in Service | 26. Repara Vehicul | 27. Raport Tehnic\n";
    std::cout << "28. Vinde Bilet | 29. Simulare Automata (Fisier) | 0. Iesire\n";
    std::cout << "Optiunea ta: ";
}

int main() {
    Dispecerat dispecerat;
    int optiune = -1;

    while (true) {
        afiseazaMeniu();
        if (!(std::cin >> optiune)) {
            if (std::cin.eof()) break;
            curataInput();
            continue;
        }

        if (optiune == 0) break;

        try {
            switch (optiune) {
            case 1: {
                int tip, id, cap;
                std::cout << "Tip (1-Autobuz, 2-Tramvai, 3-Metrou): ";
                if (!(std::cin >> tip >> id >> cap)) throw TransportException("Input vehicul invalid");
                auto v = VehiculFactory::creeazaVehicul(tip, id, cap);
                dispecerat.adaugaVehicul(*v);
                break;
            }
            case 2: {
                int id;
                std::cout << "ID vehicul: ";
                if (!(std::cin >> id)) throw TransportException("ID invalid");
                dispecerat.stergeVehicul(id);
                break;
            }
            case 3:
                dispecerat.afiseazaVehicule();
                break;
            case 4: {
                std::string nume;
                double dist;
                curataInput();
                std::cout << "Nume ruta: ";
                if (!std::getline(std::cin, nume) || nume.empty()) throw TransportException("Nume ruta invalid");
                std::cout << "Distanta (km): ";
                if (!(std::cin >> dist)) throw TransportException("Distanta invalida");
                dispecerat.adaugaRuta(Ruta(nume, dist));
                break;
            }
            case 5:
                dispecerat.afiseazaRute();
                break;
            case 6: {
                int tipInt, impact;
                std::string desc;
                std::cout << "Tip (0-3): ";
                if (!(std::cin >> tipInt >> impact)) throw TransportException("Input incident invalid");
                curataInput();
                std::cout << "Descriere: ";
                if (!std::getline(std::cin, desc)) throw TransportException("Descriere incident invalida");
                dispecerat.adaugaIncident(Incident(static_cast<TipIncident>(tipInt), desc, impact));
                break;
            }
            case 7:
                dispecerat.afiseazaIncidente();
                break;
            case 8: {
                std::string nume;
                curataInput();
                std::cout << "Nume ruta: ";
                if (!std::getline(std::cin, nume)) throw TransportException("Ruta invalida");
                std::cout << "Timp: " << dispecerat.calculeazaTimpTotal(nume) << "\n";
                break;
            }
            case 11: {
                int id;
                std::string nume;
                std::cout << "ID: ";
                if (!(std::cin >> id)) throw TransportException("ID invalid");
                curataInput();
                std::cout << "Ruta: ";
                if (!std::getline(std::cin, nume)) throw TransportException("Ruta invalida");
                std::cout << "Timp: " << dispecerat.simuleazaCursa(id, nume) << "\n";
                break;
            }
            case 12:
                Persistenta::salveazaSistem(dispecerat, "sistem.txt");
                break;
            case 13:
                Persistenta::incarcaSistem(dispecerat, "sistem.txt");
                break;
            case 23:
                std::cout << "Venituri: " << dispecerat.calculeazaVenituriTotale() << " RON\n";
                break;
            case 25: {
                int id;
                std::string motiv;
                std::cout << "ID: ";
                if (!(std::cin >> id)) throw TransportException("ID invalid");
                curataInput();
                std::cout << "Motiv: ";
                if (!std::getline(std::cin, motiv)) throw TransportException("Motiv invalid");
                dispecerat.getManagementTehnic().trimiteInService(id, motiv);
                break;
            }
            case 28: {
                int tipB;
                double pret;
                std::cout << "1. Intreg | 2. Redus: ";
                if (!(std::cin >> tipB >> pret)) throw TransportException("Input bilet invalid");
                if (tipB == 2) dispecerat.vindeBilet(true, pret, 0.5);
                else dispecerat.vindeBilet(false, pret);
                break;
            }
            case 29: {
                std::ifstream fin("tastatura.txt");
                if (!fin) break;
                dispecerat.sorteazaVehiculeDupaCapacitate();
                int idV; std::string rN;
                for (int i = 0; i < 3; ++i) {
                    if (fin >> idV >> rN) {
                        try {
                            dispecerat.simuleazaCursa(idV, rN);
                        } catch (...) {}
                    }
                }
                fin.close();
                break;
            }
            default:
                break;
            }
        } catch (const std::exception& e) {
            std::cerr << "Eroare: " << e.what() << "\n";
            curataInput();
        }
    }
    return 0;
}