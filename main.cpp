#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "Dispecerat.hpp"
#include "Vehicul.hpp"
#include "Logger.hpp"
#include "Persistenta.hpp"
#include "Statistici.hpp"
#include "VehiculFactory.hpp"
#include "Mentenanta.hpp"
#include "Statistica.hpp"
#include "Incident.hpp"

template <typename T, typename V>
bool verificaTip(const V* vehicul) {
    return dynamic_cast<const T*>(vehicul) != nullptr;
}

void curataInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void populeazaDateTest(Dispecerat& d) {
    try {
        d.adaugaVehicul(*VehiculFactory::creeazaVehicul(1, 101, 50));
        d.adaugaVehicul(*VehiculFactory::creeazaVehicul(2, 202, 100));
        d.adaugaRuta(Ruta("Traseu Test", 10.5));
        d.vindeBilet(false, 5.0);
    } catch (...) {}
}

int main() {
    Dispecerat dispecerat;
    populeazaDateTest(dispecerat);

    std::string inputUtilizator;

    while (true) {
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
        std::cout << "28. Vinde Bilet | 29. Audit Complet | 0. Iesire\n";
        std::cout << "Optiunea ta: ";

        if (!(std::cin >> inputUtilizator)) break;

        int optiune;
        try {
            optiune = std::stoi(inputUtilizator);
        } catch (...) {
            continue;
        }

        if (optiune == 0) break;

        try {
            switch (optiune) {
            case 1: {
                int t, id, c;
                if (!(std::cin >> t >> id >> c)) { curataInput(); break; }
                dispecerat.adaugaVehicul(*VehiculFactory::creeazaVehicul(t, id, c));
                break;
            }
            case 2: {
                int id;
                if (!(std::cin >> id)) { curataInput(); break; }
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
                if (!std::getline(std::cin, nume) || nume.empty()) break;
                if (!(std::cin >> dist)) { curataInput(); break; }
                dispecerat.adaugaRuta(Ruta(nume, dist));
                break;
            }
            case 5:
                dispecerat.afiseazaRute();
                break;
            case 6: {
                int ti, imp;
                std::string desc;
                if (!(std::cin >> ti >> imp)) { curataInput(); break; }
                curataInput();
                if (!std::getline(std::cin, desc)) break;
                dispecerat.adaugaIncident(Incident(static_cast<TipIncident>(ti), desc, imp));
                break;
            }
            case 7:
                dispecerat.afiseazaIncidente();
                break;
            case 8: {
                std::string n;
                curataInput();
                if (!std::getline(std::cin, n)) break;
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
                int id;
                std::string n;
                if (!(std::cin >> id)) { curataInput(); break; }
                curataInput();
                if (!std::getline(std::cin, n)) break;
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
                if (!std::getline(std::cin, n)) break;
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
                if (!std::getline(std::cin, n)) break;
                if (const auto* v = Statistici::vehiculCelMaiRapid(dispecerat, n))
                    std::cout << "ID: " << v->getId() << "\n";
                break;
            }
            case 20:
                if (const auto* v = Statistici::vehiculCapacitateMaxima(dispecerat))
                    std::cout << "ID: " << v->getId() << "\n";
                break;
            case 21: {
                std::string n;
                curataInput();
                if (!std::getline(std::cin, n)) break;
                std::cout << "Medie: " << Statistici::timpMediuPeRuta(dispecerat, n) << "\n";
                break;
            }
            case 22:
                dispecerat.genereazaRaportActivitate();
                break;
            case 23:
                std::cout << "Venituri: " << dispecerat.calculeazaVenituriTotale() << "\n";
                break;
            case 24: {
                std::string n;
                curataInput();
                if (!std::getline(std::cin, n)) break;
                Statistici::recomandaVehiculOptim(dispecerat, n);
                break;
            }
            case 25: {
                int id;
                std::string m;
                if (!(std::cin >> id)) { curataInput(); break; }
                curataInput();
                if (!std::getline(std::cin, m)) break;
                dispecerat.getManagementTehnic().trimiteInService(id, m);
                break;
            }
            case 26: {
                int id;
                if (!(std::cin >> id)) { curataInput(); break; }
                dispecerat.getManagementTehnic().reparaVehicul(id);
                break;
            }
            case 27:
                dispecerat.getManagementTehnic().genereazaRaportTehnic();
                break;
            case 28: {
                int tb;
                double pr;
                if (!(std::cin >> tb >> pr)) { curataInput(); break; }
                if (tb == 2) dispecerat.vindeBilet(true, pr, 0.5);
                else dispecerat.vindeBilet(false, pr);
                break;
            }
            case 29: {
                std::cout << "Audit: " << dispecerat.numaraVehiculeDeTip<Autobuz>() << "\n";
                for (const auto* v : dispecerat.getVehicule()) {
                    if (verificaTip<Autobuz>(v)) std::cout << "ID " << v->getId() << " OK\n";
                    if (const auto* b = dynamic_cast<const Bilet*>(v)) std::cout << "S: " << b->getSerie() << "\n";
                }
                int km = dispecerat.getManagementTehnic().getKilometri(101);
                dispecerat.getManagementTehnic().adaugaNotitaTehnica(101, "Audit");
                Statistica<double> stAudit("Audit");
                if (stAudit.goala()) stAudit.adauga(static_cast<double>(km));
                dispecerat.sorteazaVehiculeDupaCapacitate();
                dispecerat.filtreazaVehiculeDupaTip("Autobuz");
                SistemTicketing& tkt = dispecerat.getSistemTicketing();
                tkt.afiseazaIstoric();
                tkt.anuleazaUltimulBilet();
                tkt.curataIstoric();
                Incident auditInc(TipIncident::ACCIDENT, "Audit", 0);
                auditInc.setImpactMinute(15);
                auditInc.setDescriere("Audit");
                Persistenta::creeazaBackup("sistem.txt", "backup.txt");
                afiseazaAuditGeneric(dispecerat);
                Logger::getInstance().log(LogLevel::INFO, "Audit OK");
                break;
            }
            default:
                break;
            }
        } catch (const std::exception& e) {
            std::cerr << "E: " << e.what() << "\n";
        }
    }
    return 0;
}