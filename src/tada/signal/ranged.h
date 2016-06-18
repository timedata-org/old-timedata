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

    Ranged() : value_(0) {}
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

    Ranged invert() const {
        // TODO: this is basically bogus for the general case.  :-)
        if (Range::start < 0)
            return -value_;
        // TODO: what if start > 0?  Why would this be?
        return (value_ > 0 ? Range::range: -Range::range) - value_;
    }

    template <typename Range2>
    operator Ranged<Range2>() const {
        return tada::scale<Range2>(tada::unscale<Range>(value_));
    }

    operator value_type&() { return value_; }
    operator value_type() const { return value_; }

    value_type& operator*() { return value_; }
    value_type operator*() const { return value_; }

    Ranged operator-() const { return {-value_}; }

    Ranged operator+(Ranged const& x) const { return {value_ + x.value_}; }
    Ranged operator-(Ranged const& x) const { return {value_ - x.value_}; }
    Ranged operator*(Ranged const& x) const { return {value_ * x.value_}; }
    Ranged operator/(Ranged const& x) const {
        return divPython(value_, x.value_);
    }

    Ranged& operator+=(Ranged const& x) {
        value_ += x.value_;
        return *this;
    }

    Ranged& operator-=(Ranged const& x) {
        value_ -= x.value_;
        return *this;
    }

    Ranged& operator*=(Ranged const& x) {
        value_ *= x.value_;
        return *this;
    }

    Ranged& operator/=(Ranged const& x) {
        value_ = divPython(value_, x.value_);
        return *this;
    }

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
