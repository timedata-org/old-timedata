#pragma once

#include <tada/signal/range.h>

namespace tada {

/** A Ranged number looks like an underlying numeric type, but with a
    generically attached Range.

    "Generic" means that there is no cost at run-time to carrying this
    information around - the downside is that we have to instantiate a new
    template for each range we want, but since the total number is very small,
    this is almost free. */
template <typename Range>
class Ranged {
  public:
    using value_type = ValueType<Range>;

    Ranged() = default;
    Ranged(Ranged const&) = default;
    Ranged(Ranged&&) = default;
    Ranged(value_type n) : value_(n) {}
    Ranged& operator=(Ranged const&) = default;

    value_type unscale() const {
        return tada::unscale<Range>(value_);
    }

    static Ranged scale(value_type v) {
        return tada::scale<Range>(v);
    }

    template <typename Range2>
    operator Ranged<Range2>() const {
        return tada::scale<Range2>(tada::unscale<Range>(value_));
    }

    operator value_type() const { return value_; }
    operator value_type&() { return value_; }

    Ranged operator-() const { return {-value_}; }

    Ranged operator+(Ranged const& x) const { return {value_ + x.value_}; }
    Ranged operator-(Ranged const& x) const { return {value_ - x.value_}; }
    Ranged operator*(Ranged const& x) const { return {value_ * x.value_}; }
    Ranged operator/(Ranged const& x) const {
        return divPython(value_, x.value_);
    }

    Ranged operator+=(Ranged const& x) { value_ += x.value_; }
    Ranged operator-=(Ranged const& x) { value_ -= x.value_; }
    Ranged operator*=(Ranged const& x) { value_ *= x.value_; }
    Ranged operator/=(Ranged const& x) { value_ = divPython(value_, x.value_); }

    bool operator==(Ranged const& x) const { return value_ == x.value_; }
    bool operator!=(Ranged const& x) const { return value_ != x.value_; }
    bool operator<(Ranged const& x) const { return value_ < x.value_; }
    bool operator<=(Ranged const& x) const { return value_ <= x.value_; }
    bool operator>(Ranged const& x) const { return value_ > x.value_; }
    bool operator>=(Ranged const& x) const { return value_ >= x.value_; }

  private:
    value_type value_;
};

}  // tada
