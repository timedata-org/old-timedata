#pragma once

#include <functional>

#include <timedata/signal/convert_inl.h>

namespace timedata {
namespace color_list {

using RGBIndexer = std::function<ColorRGB (size_t index)>;

template <typename ColorList>
RGBIndexer getIndexer(ColorList const& colors) {
    return [&] (size_t i) {
        ColorRGB result;
        converter::convertSample(colors[i], result);
        return result;
    };
}

struct RGBIndexIterator {
    RGBIndexer indexer;
    size_t start;
    size_t finish;

    struct iterator {
        RGBIndexIterator& parent;
        size_t i;
        /* TODO: lots more stuff here.
        https://stackoverflow.com/questions/8054273

        bool operator==(iterator x) { return i == x.i; }
        bool operator!=(iterator x) { return i != x.i; }
        void operator++( */
    };

    iterator begin() { return {*this, start}; }
    iterator end() { return {*this, finish}; }
};

}  // timedata
}  // color_list
