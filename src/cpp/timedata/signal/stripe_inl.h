#pragma once

#include <timedata/signal/stripe.h>

namespace timedata {

Stripe::Iterator::Iterator(Stripe const& stripe, size_t size)
        : stripe_(stripe),
          size_(size),
          index_(stripe.begin),
          done_(not stripe.skip) {
    adjustIndex();
}

inline void Stripe::Iterator::adjustIndex() {
    auto repeat = [&]() {
        done_ = (stripe_.repeats <= ++repeat_ or not stripe_.repeats);
        return done_;
    };

    while (not done_) {
        if (stripe_.skip > 0 and index_ > size_ and repeat())
            index_ = stripe_.reflect ? 2 * size_ - index_ : index_ - size_;
        else if (stripe_.skip < 0 and index_ < 0 and repeat())
            index_ = stripe_.reflect ? - index_ : index_ + size_;
        else
            return;
    }
    /* TODO: this is pretty neat, but inefficient if index_ is
       either very much bigger than size_ or very negative. */
}

inline void Stripe::Iterator::next() {
    if (not done_) {
        log("Iterating when done!");
        return;
    }

    index_ += stripe_.skip;
    adjustIndex();
}

} // timedata
