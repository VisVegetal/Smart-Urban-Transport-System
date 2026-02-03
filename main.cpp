#include <iostream>
#include <limits>
#include <string>

#include "Dispecerat.hpp"
#include "Autobuz.hpp"
#include "Tramvai.hpp"
#include "Metrou.hpp"
#include "Exceptii.h"

void afiseazaMeniu() {
    std::cout << "\n===== SMART URBAN TRANSPORT SYSTEM =====\n";
    std::cout << "1. Adauga vehicul\n";
    std::cout << "2. Sterge vehicul\n";
    std::cout << "3. Afiseaza vehicule\n";
    std::cout << "4. Adauga ruta\n";
    std::cout << "5. Afiseaza rute\n";
    std::cout << "6. Adauga incident\n";
    std::cout << "7. Afiseaza incidente\n";
    std::cout << "8. Calculeaza timp total pe ruta\n";
    std::cout << "0. Iesire\n";
    std::cout << "Optiune: ";
}

void curataInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Dispecerat dispecerat;
    int optiune = -1;

    while (true) {
        try {
            afiseazaMeniu();
            std::cin >> optiune;

            if (std::cin.fail()) {
                curataInput();
                throw TransportException("Input invalid.");
            }

            if (optiune == 0) {
                std::cout << "Iesire aplicatie.\n";
                break;
            }

            switch (optiune) {

            case 1: { // Adauga vehicul
                int tip, id, capacitate;

                std::cout << "Tip vehicul (1-Autobuz, 2-Tramvai, 3-Metrou): ";
                std::cin >> tip;

                std::cout << "ID vehicul: ";
                std::cin >> id;

                std::cout << "Capacitate: ";
                std::cin >> capacitate;

                if (tip == 1) {
                    Autobuz a(id, capacitate);
                    dispecerat.adaugaVehicul(a);
                } else if (tip == 2) {
                    Tramvai t(id, capacitate);
                    dispecerat.adaugaVehicul(t);
                } else if (tip == 3) {
                    Metrou m(id, capacitate);
                    dispecerat.adaugaVehicul(m);
                } else {
                    throw TransportException("Tip vehicul invalid.");
                }

                std::cout << "Vehicul adaugat cu succes.\n";
                break;
            }

            case 2: { // Sterge vehicul
                int id;
                std::cout << "ID vehicul de sters: ";
                std::cin >> id;

                dispecerat.stergeVehicul(id);
                std::cout << "Vehicul sters.\n";
                break;
            }

            case 3: { // Afiseaza vehicule
                dispecerat.afiseazaVehicule();
                break;
            }

            case 4: { // Adauga ruta
                std::string nume;
                double distanta;

                curataInput();
                std::cout << "Nume ruta: ";
                std::getline(std::cin, nume);

                std::cout << "Distanta (km): ";
                std::cin >> distanta;

                Ruta r(nume, distanta);
                dispecerat.adaugaRuta(r);

                std::cout << "Ruta adaugata.\n";
                break;
            }

            case 5: { // Afiseaza rute
                dispecerat.afiseazaRute();
                break;
            }

            case 6: { // Adauga incident
                int tip, impact;
                std::string descriere;

                std::cout << "Tip incident (1-Trafic, 2-Intarziere, 3-Defectiune, 4-Accident): ";
                std::cin >> tip;

                std::cout << "Impact (minute): ";
                std::cin >> impact;

                curataInput();
                std::cout << "Descriere: ";
                //std::getline(std::cin, descriere);
                std::getline(std::cin, descriere);

                TipIncident ti;
                switch (tip) {
                    case 1: ti = TipIncident::TRAFIC_INTENS; break;
                    case 2: ti = TipIncident::INTARZIERE; break;
                    case 3: ti = TipIncident::DEFECTIUNE; break;
                    case 4: ti = TipIncident::ACCIDENT; break;
                    default:
                        throw TransportException("Tip incident invalid.");
                }

                Incident inc(ti, descriere, impact);
                dispecerat.adaugaIncident(inc);

                std::cout << "Incident adaugat.\n";
                break;
            }

            case 7: { // Afiseaza incidente
                dispecerat.afiseazaIncidente();
                break;
            }

            case 8: { // Calculeaza timp total
                std::string numeRuta;

                curataInput();
                std::cout << "Nume ruta: ";
                std::getline(std::cin, numeRuta);

                double timp = dispecerat.calculeazaTimpTotal(numeRuta);
                std::cout << "Timp total estimat: " << timp << " ore\n";
                break;
            }

            default:
                std::cout << "Optiune invalida.\n";
                break;
            }
        }
        catch (const TransportException& e) {
            std::cerr << "Eroare: " << e.what() << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Eroare standard: " << e.what() << "\n";
        }
    }

    return 0;
}
