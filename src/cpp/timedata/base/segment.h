#pragma once

#include <timedata/base/base.h>

namespace timedata {

template <typename T>
struct Segment {
    T& start;
    size_t size;

    using iterator = T*;

    iterator begin() { return &start; }
    iterator end() { return begin() + size; }

    T& operator[](size_t i) { return *(begin() + i); }
};

template <typename T>
Segment<T> makeSegment(T& start, size_t size} {
    return {start, size};
}

} // namespace
