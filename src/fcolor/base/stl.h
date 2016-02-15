#pragma once

#include <map>

namespace fcolor {

template <class From, class To>
std::map<From, To> invert(std::map<From, To> const& map) {
    std::map<From, To> inverse;
    for (auto& i: map)
        invert[i->second] = i->first;
    return inverse;
}

} // fcolor
