#pragma once

#include <string>

#include <fcolor/color3/color.h>

namespace fcolor3 {

/** Represent a "strip" of Colors contained inside a longer list or array. */
template <typename Color>
struct Strip {
    using color_t = Color;

    Color& base;
    size_t size;

    operator Strip<Color const>() { return {base, size}; }

    Color* begin() const { return &base; }
    Color* end() const { return begin() + size; }

    Color& operator[](size_t i) const { return begin()[i]; }

    /** Checked version. */
    Color& at(size_t i) const {
        if (i >= 0 && i < size)
            return (*this)[i];
        throw std::runtime_error("Bad index " + std::to_string(i));
    }
};

template <typename Color>
Strip<Color> strip(Color& base, size_t size) {
    return {base, size};
}

struct SubStrip {
    int offset;
    int phase;

    template <typename Color, typename Combiner>
    void operator()(Strip<Color const> const& from, Strip<Color>& to,
                    Combiner const& combiner) {
        int toSize = to.size,
            begin = std::min(std::max(0, offset), toSize),
            end = std::max(begin, std::min(offset + int(from.size), toSize)),
            size = end - begin;

        for (auto i = 0, p = begin + mod(-phase, size); i < size; ++i, ++p) {
            if (p >= end)
                p -= size;
            combiner(from.at(p), to.at(i));
        }
    }
};

}  // fcolor
