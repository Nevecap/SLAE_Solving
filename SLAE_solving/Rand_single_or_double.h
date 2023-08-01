#pragma once
#include <functional>
#include <random>

template<typename T>
class Rand_single_or_double
{
    static_assert(std::is_same<T, float>::value || std::is_same<T, double>::value);
public:
    Rand_single_or_double(double low, double high)
        :r(std::bind(std::uniform_real_distribution<>(low, high), std::default_random_engine())) {}

    double operator()() { return r(); }

private:
    std::function<T()> r;
};