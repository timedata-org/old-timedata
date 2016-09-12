#pragma once

#include <stdint.h>
#include <type_traits>
#include <vector>

namespace timedata {

using Permutation = std::vector<uint8_t>;
using Permutations = std::vector<Permutation>;

/** Return a list of all the permutations of [0, n). */
Permutations permutations(uint8_t n);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Implementation details follow.
//
inline Permutations permutations(uint8_t n) {
    Permutation perm;
    for (uint8_t i = 0; i < n; ++i)
        perm.push_back(i);

    Permutations result;
    do {
        result.push_back(perm);
    } while (std::next_permutation(perm.begin(), perm.end()));

    return result;
}

} // timedata
