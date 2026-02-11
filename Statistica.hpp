#ifndef STATISTICA_HPP
#define STATISTICA_HPP

#include <vector>
#include <numeric>
#include <cstddef>

// clasa template generica pentru calcule statistice
template <typename T>
class Statistica {
private:
    std::vector<T> valori; // atribut dependent de T

public:
    Statistica() = default;

    // adauga o valoare
    void adauga(const T& v) {
        valori.push_back(v);
    }

    // suma valorilor
    T suma() const {
        return std::accumulate(valori.begin(), valori.end(), T{});
    }

    // media valorilor
    [[nodiscard]] double medie() const {
        if (valori.empty())
            return 0.0;
        return static_cast<double>(suma()) / valori.size();
    }

    [[nodiscard]] std::size_t dimensiune() const {
        return valori.size();
    }

    [[nodiscard]] bool goala() const {
        return valori.empty();
    }
};

#endif
