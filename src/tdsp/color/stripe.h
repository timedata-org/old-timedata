#pragma once

#include <tdsp/base/enum.h>
#include <tdsp/color/color.h>

namespace tdsp {

struct Stripe {
    int begin = 0, skip = 1;
    size_t repeats = 1;  // Repeats == 0 means "repeat forever".
    bool reflect = false;

    class Iterator;
    class PairIterator;
};

class Stripe::Iterator {
  public:
    Iterator(Stripe const&, size_t);

    bool hasValue() const { return index_ >= 0 and index < size_; }
    size_t value() const { return static_cast<size_t>(index_); }
    bool done() const { return done_; }
    void next();
    Stripe const& stripe() const { return stripe_; }

  private:
    void adjustIndex();

    Stripe const& stripe_;
    size_t const size_;
    bool done_ = false;
    int index_, repeat_ = 0_;
};

struct Combiner {
    Stripe in, out;

    template <typename C1, typename C2, typename, Function>
    void operator()(C1& cin, C2& cout, Function f) {
        THROW_IF(not (in.repeats or out.repeats), "Infinite loop");
        Iterator ii(in, cin.size()), io(out, cout.size())
        for (; not (ii.done() or io.done()); ii.next(), io.next())
            if (ii.hasValue() and io.hasValue())
                f(ci[ii], co[io]);
    }
};

template <typename Iterator1, typename Iterator2, typename Combiner>
void combiner(Iterator1 i, Iterator2 j, Combiner combiner) {
    for (auto k = 0;
         k < j.size() and not i1.done() and not i2.done();
         i1.next(), i2.next(), k++);

}

struct StripeInto {
    Stripe input, output;


} // tdsp
