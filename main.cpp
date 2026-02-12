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
    if (std::cin.fail()) {
        std::cin.clear();
    }
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
            std::cin.clear();
            curataInput();
            continue;
        }

        if (optiune == 0) break;

        try {
            switch (optiune) {
            case 1: {
                int tip, id, cap;
                std::cout << "Tip (1-Autobuz, 2-Tramvai, 3-Metrou): "; std::cin >> tip;
                std::cout << "ID: "; std::cin >> id;
                std::cout << "Capacitate: "; std::cin >> cap;
                auto v = VehiculFactory::creeazaVehicul(tip, id, cap);
                dispecerat.adaugaVehicul(*v);
                break;
            }
            case 2: {
                int id;
                std::cout << "ID vehicul: "; std::cin >> id;
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
                std::cout << "Nume ruta: "; std::getline(std::cin, nume);
                std::cout << "Distanta (km): ";
                if (!(std::cin >> dist)) {
                    std::cin.clear();
                    curataInput();
                    throw TransportException("Distanță invalidă.");
                }
                dispecerat.adaugaRuta(Ruta(nume, dist));
                break;
            }
            case 5:
                dispecerat.afiseazaRute();
                break;
            case 6: {
                int tipInt, impact;
                std::string desc;
                std::cout << "Tip (0-3): "; std::cin >> tipInt;
                std::cout << "Impact: "; std::cin >> impact;
                curataInput();
                std::cout << "Descriere: "; std::getline(std::cin, desc);
                dispecerat.adaugaIncident(Incident(static_cast<TipIncident>(tipInt), desc, impact));
                break;
            }
            case 7:
                dispecerat.afiseazaIncidente();
                break;
            case 8: {
                std::string nume;
                curataInput();
                std::cout << "Nume ruta: "; std::getline(std::cin, nume);
                std::cout << "Timp: " << dispecerat.calculeazaTimpTotal(nume) << "\n";
                break;
            }
            case 9:
                Logger::getInstance().afiseazaLoguri();
                break;
            case 10:
                Logger::getInstance().salveazaInFisier("loguri.txt");
                break;
            case 11: {
                int id;
                std::string nume;
                std::cout << "ID: "; std::cin >> id;
                curataInput();
                std::cout << "Ruta: "; std::getline(std::cin, nume);
                std::cout << "Timp: " << dispecerat.simuleazaCursa(id, nume) << "\n";
                break;
            }
            case 12:
                Persistenta::salveazaSistem(dispecerat, "sistem.txt");
                break;
            case 13:
                Persistenta::incarcaSistem(dispecerat, "sistem.txt");
                break;
            case 14:
                Statistici::raportDetaliat(dispecerat);
                break;
            case 15:
                Statistici::distributieVehicule(dispecerat);
                break;
            case 16: {
                std::string nume;
                curataInput();
                std::cout << "Nume ruta: "; std::getline(std::cin, nume);
                dispecerat.stergeRuta(nume);
                break;
            }
            case 17:
                if (Persistenta::esteFisierValid("sistem.txt")) std::cout << "Valid.\n";
                break;
            case 18:
                Statistici::raportGeneral(dispecerat);
                break;
            case 19: {
                std::string nume;
                curataInput();
                std::cout << "Ruta: "; std::getline(std::cin, nume);
                if (auto v = Statistici::vehiculCelMaiRapid(dispecerat, nume); v != nullptr) {
                    std::cout << "Rapid: " << v->getId() << "\n";
                }
                break;
            }
            case 20: {
                if (auto v = Statistici::vehiculCapacitateMaxima(dispecerat); v != nullptr) {
                    std::cout << "Capacitate: " << v->getId() << "\n";
                }
                break;
            }
            case 21: {
                std::string nume;
                curataInput();
                std::cout << "Ruta: "; std::getline(std::cin, nume);
                std::cout << "Mediu: " << Statistici::timpMediuPeRuta(dispecerat, nume) << "\n";
                break;
            }
            case 22:
                dispecerat.genereazaRaportActivitate();
                break;
            case 23:
                std::cout << "Venituri: " << dispecerat.calculeazaVenituriTotale() << "\n";
                break;
            case 24: {
                std::string nume;
                curataInput();
                std::cout << "Ruta: "; std::getline(std::cin, nume);
                Statistici::recomandaVehiculOptim(dispecerat, nume);
                break;
            }
            case 25: {
                int id;
                std::string motiv;
                std::cout << "ID: "; std::cin >> id;
                curataInput();
                std::cout << "Motiv: "; std::getline(std::cin, motiv);
                dispecerat.getManagementTehnic().trimiteInService(id, motiv);
                break;
            }
            case 26: {
                int id;
                std::cout << "ID: "; std::cin >> id;
                dispecerat.getManagementTehnic().reparaVehicul(id);
                break;
            }
            case 27:
                dispecerat.getManagementTehnic().genereazaRaportTehnic();
                break;
            case 28: {
                int tipB;
                double pret;
                std::cout << "1. Intreg | 2. Redus: "; std::cin >> tipB;
                std::cout << "Pret: "; std::cin >> pret;
                if (tipB == 2) dispecerat.vindeBilet(true, pret, 0.5);
                else dispecerat.vindeBilet(false, pret);
                break;
            }
            case 29: {
                std::cout << "--- SIMULARE AUTOMATA ---\n";
                std::ifstream fin("tastatura.txt");
                if (!fin) break;
                dispecerat.sorteazaVehiculeDupaCapacitate();
                dispecerat.filtreazaVehiculeDupaTip("Autobuz");
                int idV; std::string rN;
                for (int i = 0; i < 3; ++i) {
                    if (fin >> idV >> rN) {
                        try {
                            dispecerat.simuleazaCursa(idV, rN);
                            if (dispecerat.getManagementTehnic().getKilometri(idV) >= 0) {
                                std::string n; fin >> n;
                                dispecerat.getManagementTehnic().adaugaNotitaTehnica(idV, n);
                            }
                        } catch (...) {}
                    }
                }
                std::string d; int imp;
                while (fin >> d >> imp) {
                    Incident a(TipIncident::ACCIDENT, d, imp);
                    a.setImpactMinute(imp + 10);
                    a.setDescriere("SIM: " + d);
                    dispecerat.adaugaIncident(a);
                }
                dispecerat.vindeBilet(false, 3.0);
                const SistemTicketing& tkt = dispecerat.getSistemTicketing();
                tkt.afiseazaIstoric();
                SistemTicketing& tktM = dispecerat.getSistemTicketing();
                tktM.anuleazaUltimulBilet();
                Statistica<double> st;
                st.adauga(10.0);
                if (!st.goala()) std::cout << st.dimensiune() << "\n";
                Persistenta::creeazaBackup("sistem.txt", "backup.txt");
                tktM.curataIstoric();
                for (const auto v : dispecerat.getVehicule()) {
                    if (v->getId() == -999) {
                        if (const auto* ptr = dynamic_cast<const Bilet*>(v)) {
                            std::cout << ptr->getSerie();
                        }
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
        }
    }
    return 0;
}