#pragma once

#include <string>
#include <fcolor/color3/color.h>

namespace fcolor3 {

/** Represent a "strip" of Colors contained inside a longer list or array. */
template <typename Color>
class Strip {
  public:
    using color_t = Color;

    Strip(Color& b, size_t s)             : base_(b), size_(s) {}
    Strip(typename Color::List& cl)       : base_(cl[0]), size_(cl.size()) {}
    Strip(typename Color::List const& cl) : base_(cl[0]), size_(cl.size()) {}

    size_t size() const { return size; }

    Color* begin() const { return &base_; }
    Color* end() const { return begin() + size_; }

    Color& operator[](size_t i) const { return begin()[i]; }

    /** Checked version. */
    Color& at(size_t i) const {
        if (i >= 0 && i < size_)
            return (*this)[i];
        throw std::runtime_error("Bad index " + std::to_string(i));
    }

    operator Strip<Color const>() { return {base_, size_}; }

  private:
    Color& base_;
    size_t size_;
};

template <typename Color>
Strip<Color> strip(Color& base, size_t size) {
    return {base, size};
}

template <typename Color>
Strip<Color> strip(typename Color::List& colorList) {
    return {colorList[0], colorList.size(); }
}

template <typename Color>
Strip<Color const> strip(typename Color::List const& colorList) {
    return {colorList[0], colorList.size(); }
}

struct SubStrip {
    int offset;
    int phase;

    template <typename Color, typename Combiner>
    void operator()(Strip<Color const> const& from, Strip<Color>& to,
                    Combiner const& combiner) {
        int fromSize = from.size(),
            toSize = to.size(),
            begin = std::min(std::max(0, offset), toSize),
            end = std::max(begin, std::min(offset + int(from.size), toSize)),
            size = end - begin;

        for (size_t i = 0, p = begin + mod(-phase, size); i < size; ++i, ++p) {
            if (p >= end)
                p -= size;
            combiner(from.at(p), to.at(i));
        }
    }
};

template <typename FromStrip, typename ToStrip, typename Number>
void limitTo(FromStrip const& from, ToStrip& toStrip, Number limit) {
    using ToComp = typename ToStrip::color_t::component_t;

    static auto const colorSize = FromStrip::color_t::SIZE;
    static_assert(colorSize == ToStrip::color_t::SIZE);

    auto stripSize = std::min(from.size(), to.size());
    auto fromComp = &from[0];
    auto toComp = &to[0];
    for (size_t i = 0; i < stripSize * colorSize; ++i) {
        auto f = std::max(Number(0), std::min(fromComp[i], limit);
        toComp[i] = static_cast<ToComp>(f);
    }
}

}  // fcolor
