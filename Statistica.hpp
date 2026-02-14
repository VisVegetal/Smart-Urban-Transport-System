#ifndef STATISTICA_HPP
#define STATISTICA_HPP

#include <vector>
#include <numeric>
#include <string>
#include <iostream>

template <typename T>
class Statistica {
private:
    std::vector<T> date;
    std::string numeUnitate;

public:
    Statistica() : numeUnitate("Generica") {}
    explicit Statistica(std::string unitate) : numeUnitate(std::move(unitate)) {}

    void adauga(T valoare) {
        date.push_back(valoare);
    }

    T calculeazaMedia() const {
        if (date.empty()) return T{};
        T suma = std::accumulate(date.begin(), date.end(), T{});
        return suma / static_cast<T>(date.size());
    }

    T medie() const {
        return calculeazaMedia();
    }

    [[nodiscard]] std::size_t dimensiune() const {
        return date.size();
    }

    [[nodiscard]] bool goala() const {
        return date.empty();
    }

    friend std::ostream& operator<<(std::ostream& os, const Statistica<T>& s) {
        os << "Statistica [" << s.numeUnitate << "]: ";
        for (const auto& d : s.date) os << d << " ";
        return os;
    }
};

template <typename T>
void afiseazaAuditGeneric(const T& obj) {
    std::cout << "[AUDIT TEMPLATE] Obiectul ocupa " << sizeof(obj) << " bytes in memorie.\n";
}

#endif