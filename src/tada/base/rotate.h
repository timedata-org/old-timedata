#pragma once

#include <algorithm>
#include <vector>

namespace tada {

template <typename Collection>
void rotate(Collection& coll, int pos) {
    if (int size = coll.size()) {
        pos %= size;
        if (pos < 0)
            pos += size;
        std::rotate(coll.begin(), coll.begin() + pos, coll.end());
    }
}

} // namespace tada
