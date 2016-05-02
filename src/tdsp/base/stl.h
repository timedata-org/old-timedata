#pragma once

#include <map>

namespace tdsp {

template <class From, class To>
std::map<To, From> invert(std::map<From, To> const& map) {
    std::map<To, From> result;
    for (auto& i: map)
        result[i.second] = i.first;
    return result;
}

template <class From, class To>
struct MapAndInverse {
    using Map = std::map<From, To>;
    using Inverse = std::map<To, From>;

    Map map;
    Inverse inverse;
};

template <class From, class To, class Operator>
auto operate(std::map<From, To> const& map, Operator op)
        -> std::map<From, decltype(op(map.begin()->second))>
{
    std::map<From, decltype(op(map.begin()->second))> result;
    for (auto& i: map)
        result[i.first] = op(i.second);
    return result;
}

} // tdsp
