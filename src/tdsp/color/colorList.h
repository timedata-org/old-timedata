#pragma once

#include <tdsp/base/make.h>
#include <tdsp/color/slice.h>
#include <tdsp/color/color.h>
#include <tdsp/color/names_inl.h>

namespace tdsp {

using ColorList = std::vector<Color>;

template <typename T>
std::vector<T> duplicate(std::vector<T> const& v, size_t count) {
    std::vector<T> result;
    for (auto i = 0; i < count; ++i)
        result.insert(result.end(), v.begin(), v.end());
    return result;
}

template <typename T>
void reverse(std::vector<T>& v) {
    std::reverse(v.begin(), v.end());
}

inline std::string toString(ColorList const& colors) {
    std::string result = "(";
    for (auto& c : colors) {
        if (result.size() > 1)
            result += ", ";
        auto s = toString(c);
        result += "'("[isdigit(s[0])];
        result += s;
        result += "')"[isdigit(s[0])];
    }
    result += ")";
    return result;
}

template <typename T>
std::vector<T> sliceVector(
        std::vector<T> const& in, int begin, int end, int step) {
    auto slice = make<Slice>(begin, end, step);
    std::vector<T> out;
    forEach(slice, [&](int j) { out.push_back(in[j]); });
    return out;
}

} // tdsp
