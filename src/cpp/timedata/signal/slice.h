#pragma once

#include <cmath>
#include <cstddef>
#include <type_traits>

namespace timedata {

template <typename Number>
struct Range {
    Number begin, end;

    Number size() const {
        return (begin < end) ? (end - begin) : Number(0);
    }
};

template <typename Number, typename Function>
void forEach(Range<Number> range, Function f) {
    for (auto i = range.begin; i < range.end; ++i)
        f(i);
}

template <typename Number = float>
struct Slice {
    Number begin, end;
    int step;

    size_t size() const {
        if (step > 0)
            return begin < end ? ((end - begin) / step) : 0;
        if (step < 0)
            return begin > end ? ((begin - end) / -step) : 0;
        return 0;
    }
};


template <typename Number,
          typename Function,
          typename Condition>
void forEachWhile(Slice<Number> slice, Function f, Condition cond) {
    for (auto i = slice.begin; cond(i); i += slice.step)
        f(i);
}

template <typename Number, typename Function>
void forEach(Slice<Number> slice, Function f) {
    // TODO: there was more logic here that was wrong.  Why did I feel I
    // needed that?  https://github.com/rec/timedata/issues/43
    if (slice.step > 0)
        forEachWhile(slice, f, [&](Number i) { return i < slice.end; });
    else if (slice.step < 0)
        forEachWhile(slice, f, [&](Number i) { return i > slice.end; });
}

}  // timedata
