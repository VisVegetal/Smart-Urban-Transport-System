#include <iostream>
#include <limits>
#include <string>

#include "Dispecerat.hpp"
#include "Autobuz.hpp"
#include "Exceptii.hpp"
#include "Logger.hpp"
#include "Persistenta.hpp"
#include "Statistici.hpp"
#include "VehiculFactory.hpp"
#include "Mentenanta.hpp"
#include "Ticketing.hpp"
#include "Bilet.hpp"

void afiseazaMeniu() {
    std::cout << "\n=========== SMART URBAN TRANSPORT SYSTEM ===========\n";
    std::cout << "1.  Adauga vehicul\n";
    std::cout << "2.  Sterge vehicul\n";
    std::cout << "3.  Afiseaza vehicule\n";
    std::cout << "4.  Adauga ruta\n";
    std::cout << "5.  Afiseaza rute\n";
    std::cout << "6.  Adauga incident\n";
    std::cout << "7.  Afiseaza incidente\n";
    std::cout << "8.  Calculeaza timp total pe ruta\n";
    std::cout << "9.  Afiseaza loguri\n";
    std::cout << "10. Salveaza loguri in fisier\n";
    std::cout << "11. Simuleaza cursa vehicul pe ruta\n";
    std::cout << "12. Salveaza sistemul in fisier\n";
    std::cout << "13. Incarca sistemul din fisier\n";
    std::cout << "14. Raport detaliat statistici\n";
    std::cout << "15. Distributie vehicule pe tip\n";
    std::cout << "16. Sterge ruta\n";
    std::cout << "17. Verifica fisier sistem\n";
    std::cout << "18. Salveaza raport sistem\n";
    std::cout << "19. Vehicul cel mai rapid pe ruta\n";
    std::cout << "20. Vehicul capacitate maxima\n";
    std::cout << "21. Timp mediu pe ruta\n";
    std::cout << "22. Raport general sistem\n";
    std::cout << "0.  Iesire\n";
    std::cout << "===================================================\n";
    std::cout << "Optiune: ";
}

void curataInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    //obiectul care gestioneaza intregul sistem
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

            // vehicule

            case 1: {
                int tip, id, capacitate;
                std::cout << "Tip vehicul (1-Autobuz, 2-Tramvai, 3-Metrou): ";
                std::cin >> tip;

                std::cout << "ID vehicul: ";
                std::cin >> id;

                std::cout << "Capacitate: ";
                std::cin >> capacitate;

                auto v = VehiculFactory::creeazaVehicul(tip, id, capacitate);
                dispecerat.adaugaVehicul(*v);

                std::cout << "Vehicul adaugat.\n";
                break;
            }

            case 2: {
                int id;
                std::cout << "ID vehicul de sters: ";
                std::cin >> id;

                dispecerat.stergeVehicul(id);
                std::cout << "Vehicul sters.\n";
                break;
            }

            case 3:
                dispecerat.afiseazaVehicule();
                break;

            // rute

            case 4: {
                std::string nume;
                double distanta;

                curataInput();
                std::cout << "Nume ruta: ";
                std::getline(std::cin, nume);

                std::cout << "Distanta (km): ";
                std::cin >> distanta;

                dispecerat.adaugaRuta(Ruta(nume, distanta));
                std::cout << "Ruta adaugata.\n";
                break;
            }

            case 5:
                dispecerat.afiseazaRute();
                break;

            //incidente

            case 6: {
                int tip, impact;
                std::string descriere;

                std::cout << "Tip incident (1-Trafic, 2-Intarziere, 3-Defectiune, 4-Accident): ";
                std::cin >> tip;

                std::cout << "Impact (minute): ";
                std::cin >> impact;

                curataInput();
                std::cout << "Descriere: ";
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

                dispecerat.adaugaIncident(Incident(ti, descriere, impact));
                std::cout << "Incident adaugat.\n";
                break;
            }

            case 7:
                dispecerat.afiseazaIncidente();
                break;

            // calcule

            case 8: {
                std::string ruta;
                curataInput();
                std::cout << "Nume ruta: ";
                std::getline(std::cin, ruta);

                double timp = dispecerat.calculeazaTimpTotal(ruta);
                std::cout << "Timp total estimat: " << timp << " ore\n";
                break;
            }

            // logging

            case 9:
                Logger::getInstance().afiseazaLoguri();
                break;

            case 10:
                Logger::getInstance().salveazaInFisier("loguri.txt");
                std::cout << "Loguri salvate.\n";
                break;

            // simulare

            case 11: {
                int id;
                std::string ruta;

                std::cout << "ID vehicul: ";
                std::cin >> id;

                curataInput();
                std::cout << "Nume ruta: ";
                std::getline(std::cin, ruta);

                double timp = dispecerat.simuleazaCursa(id, ruta);
                std::cout << "Timp simulare: " << timp << " ore\n";
                break;
            }

            // persistenta

            case 12:
                Persistenta::salveaza(dispecerat, "sistem.txt");
                std::cout << "Sistem salvat.\n";
                break;

            case 13:
                dispecerat = Dispecerat();
                Persistenta::incarca(dispecerat, "sistem.txt");
                std::cout << "Sistem incarcat.\n";
                break;

            // statistici

            case 14:
                Statistici::raportDetaliat(dispecerat);
                break;

            case 15:
                Statistici::distributieVehicule(dispecerat);
                break;

            case 16: {
                std::string nume;
                curataInput();
                std::cout << "Nume ruta de sters: ";
                std::getline(std::cin, nume);

                if (!dispecerat.existaRuta(nume)) {
                    throw RutaException("Ruta nu exista.");
                }

                dispecerat.stergeRuta(nume);
                std::cout << "Ruta stearsa.\n";
                break;
            }
            case 17:
                if (Persistenta::fisierValid("sistem.txt"))
                    std::cout << "Fisier valid.\n";
                else
                    std::cout << "Fisier inexistent.\n";
                break;

            case 18:
                Persistenta::salveazaRaport(dispecerat, "raport.txt");
                std::cout << "Raport salvat.\n";
                break;

            case 19: {
                std::string ruta;
                curataInput();
                std::cout << "Ruta: ";
                std::getline(std::cin, ruta);

                const Vehicul* v = Statistici::vehiculCelMaiRapid(dispecerat, ruta);
                std::cout << "Cel mai rapid: "
                          << v->getTip() << " ID " << v->getId() << "\n";
                break;
            }

            case 20: {
                const Vehicul* v = Statistici::vehiculCapacitateMaxima(dispecerat);
                std::cout << "Capacitate maxima: "
                          << v->getTip() << " ("
                          << v->getCapacitate() << ")\n";
                break;
            }

            case 21: {
                std::string ruta;
                curataInput();
                std::cout << "Ruta: ";
                std::getline(std::cin, ruta);

                std::cout << "Timp mediu: "
                          << Statistici::timpMediuPeRuta(dispecerat, ruta)
                          << " ore\n";
                break;
            }

            case 22: {
                Statistici::raportGeneral(dispecerat);
                break;
            }

            case 23: {
                std::cout << "Venituri estimate din bilete (toate vehiculele): "
                          << dispecerat.calculeazaVenituriTotale() << " RON\n";
                break;
            }

            case 24: {
                std::string ruta;
                curataInput();
                std::cout << "Nume ruta pentru optimizare: ";
                std::getline(std::cin, ruta);
                Statistici::recomandaVehiculOptim(dispecerat, ruta);
                break;
            }

            case 25: { // Trimite in service
            int id;
            std::string motiv;
            std::cout << "ID Vehicul: "; std::cin >> id;
            curataInput();
            std::cout << "Motiv defectiune: "; std::getline(std::cin, motiv);
            dispecerat.getManagementTehnic().trimiteInService(id, motiv);
            break;
            }
            case 26: { // Finalizeaza reparatii
            int id;
            std::cout << "ID Vehicul reparat: "; std::cin >> id;
            dispecerat.getManagementTehnic().reparaVehicul(id);
            break;
            }
            case 27: { // Raport Mentenanta
            dispecerat.getManagementTehnic().genereazaRaportTehnic();
            break;
            }

            default:
                std::cout << "Optiune invalida.\n";
                break;
            }
        }
        catch (const ::TransportException& e) {
            std::cerr << "Eroare: " << e.what() << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Eroare standard: " << e.what() << "\n";
        }
    }

    return 0;
}
