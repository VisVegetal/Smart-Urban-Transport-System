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
    std::cout << "28. Vinde Bilet | 29. Simulare Automata (Audit) | 0. Iesire\n";
    std::cout << "Optiunea ta: ";
}

int main() {
    Dispecerat dispecerat;
    int optiune = -1;

    while (true) {
        afiseazaMeniu();

        if (!(std::cin >> optiune)) {
            break;
        }

        if (optiune == 0) break;

        try {
            switch (optiune) {
            case 1: {
                int t = 0, id = 0, c = 0;
                if (!(std::cin >> t >> id >> c)) return 0;
                auto v = VehiculFactory::creeazaVehicul(t, id, c);
                dispecerat.adaugaVehicul(*v);
                break;
            }
            case 2: {
                int id = 0;
                if (!(std::cin >> id)) return 0;
                dispecerat.stergeVehicul(id);
                break;
            }
            case 3:
                dispecerat.afiseazaVehicule();
                break;
            case 4: {
                std::string nume;
                double dist = 0.0;
                curataInput();
                if (!std::getline(std::cin, nume) || nume.empty()) return 0;
                if (!(std::cin >> dist)) return 0;
                dispecerat.adaugaRuta(Ruta(nume, dist));
                break;
            }
            case 5:
                dispecerat.afiseazaRute();
                break;
            case 6: {
                int ti = 0, imp = 0;
                std::string desc;
                if (!(std::cin >> ti >> imp)) return 0;
                curataInput();
                if (!std::getline(std::cin, desc)) return 0;
                dispecerat.adaugaIncident(Incident(static_cast<TipIncident>(ti), desc, imp));
                break;
            }
            case 7:
                dispecerat.afiseazaIncidente();
                break;
            case 8: {
                std::string n;
                curataInput();
                if (!std::getline(std::cin, n)) return 0;
                std::cout << "Timp: " << dispecerat.calculeazaTimpTotal(n) << "\n";
                break;
            }
            case 9:
                Logger::getInstance().afiseazaLoguri();
                break;
            case 10:
                Logger::getInstance().salveazaInFisier("audit.log");
                break;
            case 11: {
                int id = 0;
                std::string n;
                if (!(std::cin >> id)) return 0;
                curataInput();
                if (!std::getline(std::cin, n)) return 0;
                std::cout << "Rezultat: " << dispecerat.simuleazaCursa(id, n) << "\n";
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
                std::string n;
                curataInput();
                if (!std::getline(std::cin, n)) return 0;
                dispecerat.stergeRuta(n);
                break;
            }
            case 17:
                if (Persistenta::esteFisierValid("sistem.txt")) std::cout << "OK\n";
                break;
            case 18:
                Statistici::raportGeneral(dispecerat);
                break;
            case 19: {
                std::string n;
                curataInput();
                if (!std::getline(std::cin, n)) return 0;
                if (auto* v = Statistici::vehiculCelMaiRapid(dispecerat, n)) {
                    std::cout << "ID: " << v->getId() << "\n";
                }
                break;
            }
            case 20: {
                if (auto* v = Statistici::vehiculCapacitateMaxima(dispecerat)) {
                    std::cout << "ID: " << v->getId() << "\n";
                }
                break;
            }
            case 21: {
                std::string n;
                curataInput();
                if (!std::getline(std::cin, n)) return 0;
                std::cout << "Timp mediu: " << Statistici::timpMediuPeRuta(dispecerat, n) << "\n";
                break;
            }
            case 22:
                dispecerat.genereazaRaportActivitate();
                break;
            case 23:
                std::cout << "Venituri: " << dispecerat.calculeazaVenituriTotale() << " RON\n";
                break;
            case 24: {
                std::string n;
                curataInput();
                if (!std::getline(std::cin, n)) return 0;
                Statistici::recomandaVehiculOptim(dispecerat, n);
                break;
            }
            case 25: {
                int id = 0;
                std::string m;
                if (!(std::cin >> id)) return 0;
                curataInput();
                if (!std::getline(std::cin, m)) return 0;
                dispecerat.getManagementTehnic().trimiteInService(id, m);
                break;
            }
            case 26: {
                int id = 0;
                if (!(std::cin >> id)) return 0;
                dispecerat.getManagementTehnic().reparaVehicul(id);
                break;
            }
            case 27:
                dispecerat.getManagementTehnic().genereazaRaportTehnic();
                break;
            case 28: {
                int tipB = 0;
                double pret = 0.0;
                if (!(std::cin >> tipB >> pret)) return 0;
                if (tipB == 2) dispecerat.vindeBilet(true, pret, 0.5);
                else dispecerat.vindeBilet(false, pret);
                break;
            }
            case 29: {
                dispecerat.filtreazaVehiculeDupaTip("Autobuz");
                dispecerat.sorteazaVehiculeDupaCapacitate();
                Incident auditInc(TipIncident::ACCIDENT, "Audit", 5);
                auditInc.setImpactMinute(10);
                auditInc.setDescriere("Audit descriere");
                dispecerat.getManagementTehnic().adaugaNotitaTehnica(1, "Nota");
                if (dispecerat.getManagementTehnic().getKilometri(1) < 0) std::cout << "Audit\n";
                SistemTicketing& tkt = dispecerat.getSistemTicketing();
                tkt.afiseazaIstoric();
                tkt.anuleazaUltimulBilet();
                tkt.curataIstoric();
                Statistica<double> st;
                st.adauga(1.0);
                if(!st.goala()) std::cout << st.dimensiune() << "\n";
                Persistenta::creeazaBackup("sistem.txt", "backup.txt");
                for (const auto v : dispecerat.getVehicule()) {
                    if (v->getId() == -999) {
                        if (const auto* ptr = dynamic_cast<const Bilet*>(v)) {
                            std::cout << ptr->getSerie();
                        }
                    }
                }
                break;
            }
            default:
                break;
            }
        } catch (const std::exception& e) {
            std::cerr << "Eroare: " << e.what() << "\n";
            return 0;
        }
    }
    return 0;
}