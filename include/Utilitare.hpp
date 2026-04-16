#ifndef UTILITARE_HPP
#define UTILITARE_HPP

#include <vector>
#include <algorithm>

// funcție template liberă
template <typename T>
const T& maxim(const std::vector<T>& v) {
    return *std::max_element(v.begin(), v.end());
}

#endif
