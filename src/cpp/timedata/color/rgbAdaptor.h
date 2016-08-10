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

}  // timedata
}  // color_list
