#ifndef MENTENANTA_HPP
#define MENTENANTA_HPP

#include <string>
#include <vector>
#include <map>

enum class StareVehicul { FUNCTIONAL, REPARATII_NECESARE, IN_SERVICE, CASAT };

class Mentenanta {
private:
    std::map<int, StareVehicul> statusFlota;
    std::map<int, int> kmParcursi;
    std::map<int, std::vector<std::string>> istoricService;
    const int PRAG_REVIZIE = 5000;

public:
    Mentenanta() = default;
    
    void actualizeazaKilometraj(int id, int km);
    void trimiteInService(int id, const std::string& motiv);
    void reparaVehicul(int id);
    
    bool poateRula(int id) const;
    std::string getStatusDetalii(int id) const;
    void genereazaRaportTehnic() const;
    
    void adaugaNotitaTehnica(int id, const std::string& nota);
    int getKilometri(int id) const;
};

#endif