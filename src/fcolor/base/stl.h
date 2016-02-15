#pragma once

#include <map>

namespace fcolor {

template <class From, class To>
std::map<To, From> invert(std::map<From, To> const& map) {
    std::map<To, From> result;
    for (auto& i: map)
        invert[i->second] = i->first;
    return result;
}

template <class From, class To, class Operator>
auto processValue(Operator op, std::map<From, To> const& map)
        -> std::map<From, decltype(map.begin()->second)>
{
    std::map<From, decltype(map.begin().second)> result;
    for (auto& i: map)
        result[i->first] = op(i->second);
}

} // fcolor
