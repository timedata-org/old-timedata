#pragma once

#include <timedata/base/math_inl.h>
#include <timedata/base/make.h>
#include <timedata/signal/slice.h>
/*
#include <timedata/base/rotate.h>
#include <timedata/color/color.h>
#include <timedata/color/hsv_inl.h>
#include <timedata/color/names_inl.h>
*/

namespace timedata {

template <typename ColorVector>
void duplicateInto(size_t count, ColorVector&);

template <typename ColorVector>
ColorVector sliceVectorG(
        ColorVector const& in, int begin, int end, int step) {
    auto slice = make<Slice>(begin, end, step);
    ColorVector out;
    forEach(slice, [&](int j) { out.push_back(in[j]); });
    return out;
}

template <typename ColorVector>
bool sliceIntoVectorG(ColorVector const& in, ColorVector& out,
                     int begin, int end, int step) {
    auto slice = make<Slice>(begin, end, step);
    auto size = slice.size();

    if (in.size() == size) {
        auto i = in.begin();
        forEach(slice, [&](int j) { out[j] = *(i++); });
        return true;
    }

    if (step != 1)
        return false;

    auto ob = out.begin() + begin;
    if (in.size() < size) {
        // Shrink!  Copy the input, then erase the remains.
        std::copy(in.begin(), in.end(), ob);
        out.erase(ob + in.size(), ob + size);
    } else {
        // Grow!  Copy the first segment, then insert the second.
        std::copy(in.begin(), in.begin() + size, ob);
        out.insert(ob + slice.begin, in.begin() + size, in.end());
    }

    return true;
}

template <typename ColorVector>
void duplicateInto(size_t count, ColorVector& colors) {
    auto size = colors.size();
    colors.resize(size * count);

    for (auto i = colors.begin(); i < colors.end() - size; i += size)
        std::copy(i, i + size, i + size);
}

} // timedata
