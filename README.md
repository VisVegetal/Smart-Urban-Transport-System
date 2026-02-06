# Smart Urban Transport System 🚍🚋🚇

## Descriere
Smart Urban Transport System este o aplicație C++ de tip CLI care simulează funcționarea unui sistem de transport urban. Proiectul permite gestionarea vehiculelor, rutelor și incidentelor, precum și calcularea timpilor de deplasare și generarea de statistici relevante.

Aplicația este construită folosind principii de programare orientată pe obiecte, punând accent pe moștenire, polimorfism, gestionarea memoriei și tratarea excepțiilor.

---

## Funcționalități principale

- Gestionarea vehiculelor (Autobuz, Tramvai, Metrou)
- Gestionarea rutelor urbane
- Gestionarea incidentelor (trafic, întârzieri, defectiuni, accidente)
- Calcularea timpilor de deplasare pe rute
- Simularea unei curse pentru un vehicul specific
- Generarea de statistici (distribuție vehicule, rapoarte)
- Salvarea și încărcarea stării sistemului din fișiere text
- Sistem de logare a evenimentelor

---

## Structura proiectului

- **Vehicul** – clasă abstractă de bază
- **Autobuz / Tramvai / Metrou** – implementări concrete
- **Ruta** – modelează o rută urbană
- **Incident** – modelează evenimente neprevăzute
- **Dispecerat** – componenta centrală de gestionare
- **Statistici** – analiză și rapoarte
- **Persistenta** – salvare și încărcare din fișiere
- **Logger** – gestionarea logurilor
- **main.cpp** – interfața CLI




## Rulare

Aplicația rulează în consolă și oferă un meniu interactiv. Utilizatorul poate selecta opțiunile dorite introducând numărul corespunzător.

