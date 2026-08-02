#ifndef STATISTICS_SERIES_HPP
#define STATISTICS_SERIES_HPP

#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

template <typename T>
class StatisticsSeries {
private:
    std::vector<T> values;
    std::string unitName;

public:
    StatisticsSeries() : unitName("Generic") {}
    explicit StatisticsSeries(std::string unit) : unitName(std::move(unit)) {}

    void add(T value) {
        values.push_back(value);
    }

    [[nodiscard]] T computeAverage() const {
        if (values.empty()) return T{};
        T sum = std::accumulate(values.begin(), values.end(), T{});
        return sum / static_cast<T>(values.size());
    }

    [[nodiscard]] T average() const {
        return computeAverage();
    }

    [[nodiscard]] std::size_t size() const {
        return values.size();
    }

    [[nodiscard]] bool empty() const {
        return values.empty();
    }

    friend std::ostream& operator<<(std::ostream& os, const StatisticsSeries<T>& s) {
        os << "Statistics [" << s.unitName << "]: ";
        for (const auto& v : s.values) os << v << " ";
        return os;
    }
};

#endif
