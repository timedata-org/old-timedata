#pragma once

#include <tdsp/base/enum.h>
#include <tdsp/color/color.h>

namespace tdsp {

struct Stripe {
    /*
      ....d.a.b.c ->  .....2...3...1

     */

    /* Also, these variables might be negative.

       0, 0, 1:  abcd... -> 1234...

     */
    int begin, skip;
    size_t repeats = 1;
    bool reflect = false;

    class Iterator {
      public:
        Iterator(Stripe const&, size_t size);
        bool hasValue() const;
        size_t value() const { return static_cast<size_t>(index_)>; }
        bool done() const { return done_; }
        void next();

      private:
        void adjustIndex();

        Stripe const& stripe_;
        size_t const size_;
        bool done_;
        int index_, repeat_ = 0;
    };

    class Pair {
      public:
        Pair(Stripe const& s1, Stripe const& s2) : i1_(s1), i2_(s2) {}

        bool hasValue() const { return i1.hasValue() and i2.hasValue(); }
        std::pair<size_t> value() const { return {i1.value(), i2.value()}; }
        bool done() const { return i1.done() or i2.done(); }
        void next() { i1.next(); i2.next(); }

      private:
        Iterator i1_, i2_;
    }
};

} // tdsp
