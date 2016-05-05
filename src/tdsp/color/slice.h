#pragma once

#include <cmath>
#include <type_traits>

namespace tdsp {

template <typename Number>
struct Range {
    Number begin, end;
};

template <typename Number, typename Function>
void forEach(Range<Number> range, Function f) {
    for (auto i = range.begin; i < range.end; ++i)
        f(i);
}

template <typename Number>
Number size(Range<Number> r) {
    return (r.begin < r.end) ? (r.end - r.begin) : 0;
}

template <typename Number>
struct Slice {
    Number begin, end;
    int step;
};

template <typename Number,
          typename std::enable_if<std::is_signed<Number>::value, int> = 0>
Number size(Slice<Number> s) {
    if (s.step > 0)
        return (s.begin < s.end) ? (s.end - s.begin) / s.step : 0;
    if (s.step < 0)
        return (s.begin > s.end) ? (s.begin - s.end) / -s.step : 0;
    return 0;
}


template <typename Number,
          typename Function,
          typename Condition>
void forEachWhile(Slice<Number> slice, Function f, Condition cond) {
    for (auto i = slice.begin; cond(i); i += slice.step)
        f(i);

}

template <typename Number, typename Function>
void forEach(Slice<Number> slice, Function f) {
    if (slice.step > 0) {
        forEachWhile(slice, f, [&](Number i) {
            return i < slice.end and (slice.end - i) < slice.step < slice.end;
        });

    } else if (slice.step < 0) {
        forEachWhile(slice, f, [&](Number i) {
            return i > slice.end and (i - slice.end) < -slice.step;
        });
    }
}

}  // tdsp
