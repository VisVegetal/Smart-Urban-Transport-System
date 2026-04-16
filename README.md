# 🚍 Smart Urban Transport System

**Smart Urban Transport System** este o aplicație C++ de tip Command Line Interface (CLI) concepută pentru simularea și gestionarea eficientă a unei rețele de transport public. Proiectul utilizează concepte avansate de Programare Orientată pe Obiect (POO) pentru a modela interacțiunea complexă dintre vehicule, infrastructură și pasageri.

---

## ✨ Funcționalități Principale

### 🚋 Gestiune Flotă și Infrastructură
- **Sistem Multimodal:** Suport pentru vehicule de tip `Autobuz`, `Tramvai` și `Metrou`, fiecare cu logică specifică de operare.
- **Instanțiere Controlată:** Utilizarea unui `VehiculFactory` pentru crearea obiectelor într-un mod extensibil și sigur.
- **Rute și Stații:** Definirea traseelor urbane prin integrarea obiectelor de tip `Statie`, permițând o modelare realistă a hărții de transport.

### ⚙️ Mentenanță și Operațiuni
- **Modul de Mentenanță:** Urmărirea stării tehnice, a kilometrajului și gestionarea fluxului de reparații pentru fiecare vehicul în parte.
- **Ticketing & Bilete:** Sistem integrat pentru emiterea biletelor, gestionarea seriilor acestora și evidența veniturilor colectate.
- **Managementul Incidentelor:** Capacitatea de a raporta și procesa evenimente neprevăzute (accidente, blocaje) care influențează dinamica sistemului.

### 📊 Analiză și Persistență
- **Statistici Avansate:** Generarea de rapoarte detaliate prin module dedicate și utilizarea template-ului generic `Statistica` pentru prelucrarea datelor.
- **Persistența Datelor:** Salvarea și încărcarea automată a stării întregului sistem folosind fișiere externe pentru continuitatea simulării.
- **Logare Centralizată:** Monitorizarea activităților prin `Logger`, asigurând un istoric clar al tuturor evenimentelor din sistem.

### ⚠️ Tratarea Erorilor
- **Gestiune Robustă:** Utilizarea unui sistem de excepții custom pentru a trata scenariile de input invalid sau erorile de logică (ex: vehicule inexistente, rute duplicate).

---

## 🏗️ Tehnologii și Concepte Utilizate

- **Limbaj:** C++20
- **OOP:** Polimorfism, Clase Abstracte, Agregare și Compoziție.
- **Design Patterns:** Singleton (Logger), Factory (VehiculFactory).
- **STL & Genericitate:** Utilizarea intensivă a containerelor (`std::vector`), algoritmilor și a template-urilor.

