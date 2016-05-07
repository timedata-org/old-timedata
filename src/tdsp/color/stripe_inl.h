#pragma once

#include <tdsp/base/enum.h>
#include <tdsp/color/color.h>

namespace tdsp {

inline Stripe::Iterator(Stripe const& stripe, size_t size)
        : stripe_(stripe),
          size_(size),
          index_(stripe.begin),
          done_(not stripe.skip) {
    adjustIndex();
}

inline bool Stripe::hasValue() const {
    return index_ >= 0 and index < size_;
}

void Stripe::next() {
    THROW_IF(done_, "Can't call next() on a completed iterator");
    index_ += stripe_.skip;
    adjustIndex();
}

void Stripe::adjustIndex() {
    auto repeat = []() {
        done_ = (stripe_.repeats <= ++repeat_ or not stripe_.repeats);
        return done_;
    };

    /* TODO: this is pretty neat, but inefficient if index_ is
       either very much bigger than size_ or very negative. */
    while (not done_) {
        if (stripe_.skip > 0 and index_ > size_ and repeat())
            index_ = reflect_ ? 2 * size_ - index_ : index_ - size_;
        else if (stripe_.skip < 0 and index_ < 0 and repeat())
            index_ = reflect_ ? - index_ : index_ + size_;
        else
            return;
    }
}

};

} // tdsp
