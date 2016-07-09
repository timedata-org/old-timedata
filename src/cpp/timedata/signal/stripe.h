#pragma once

#include <timedata/base/enum.h>
#include <timedata/color/models/rgb.h>

namespace timedata {

struct Stripe {
    int begin = 0, skip = 1;
    size_t repeats = 1;  // Repeats == 0 means "repeat forever".
    bool reflect = false;

    class Iterator;
};

class Stripe::Iterator {
  public:
    Iterator(Stripe const&, size_t);

    bool hasValue() const { return index_ >= 0 and index_ < int(size_); }
    size_t value() const { return static_cast<size_t>(index_); }
    bool done() const { return done_; }
    void next();
    Stripe const& stripe() const { return stripe_; }

  private:
    void adjustIndex();

    Stripe const& stripe_;
    size_t const size_;
    int index_, repeat_ = 0;
    bool done_ = false;
};

template <typename C1, typename C2, typename Function>
void combine(Stripe sIn, C1& cIn, Stripe sOut, C2& cOut, Function f) {
    if (not (sIn.repeats or sOut.repeats)) {
        log("Infinite loop in combiner.");
        return;
    }

    for (Stripe::Iterator ii(sIn, cIn.size()), io(sOut, cOut.size());
         not (ii.done() or io.done()); ii.next(), io.next()) {
        if (ii.hasValue() and io.hasValue())
            f(cIn[ii], cOut[io]);
    }
}

} // timedata
