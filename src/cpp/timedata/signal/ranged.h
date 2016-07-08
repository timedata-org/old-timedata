#pragma once

#include <timedata/signal/range.h>

namespace timedata {

/** A Ranged number looks like an underlying numeric type, but with a
    generically attached Range.

    "Generic" means that there is no cost at run-time to carrying this
    information around - the downside is that we have to instantiate a new
    template for each range we want, but since the total number is very small,
    this is almost free. */
template <typename Range = Normal<>>
class Ranged {
  public:
    using value_type = ValueType<Range>;
    using range_type = Range;

    static constexpr auto START = Range::START;
    static constexpr auto RANGE = Range::RANGE;
    static constexpr auto STOP = START + RANGE;

    Ranged() : value_(0) {}
    Ranged(Ranged const&) = default;
    Ranged(Ranged&&) = default;

    // TODO: should be explicit
    Ranged(value_type n) : value_(n) {}
    Ranged& operator=(Ranged const&) = default;

    static
    Ranged scale(value_type v) { return timedata::scale<Range>(v); }
    value_type unscale() const { return timedata::unscale<Range>(value_); }

    Ranged invert() const {
        // TODO: this is basically bogus for the general case.  :-)
        if (START < 0)
            return -value_;
        // TODO: what if START > 0?  Why would this be?
        return value_ >= 0 ? (RANGE - value_): -(value_ + RANGE);
    }

    bool inBand() const { return value_ >= START and value_ <= STOP; }

    static Ranged infinity() {
        return {std::numeric_limits<value_type>::infinity()};
    }

    value_type limited() const {
        return std::max(START, std::min(STOP, value_));
    }

    // Not (yet?) used.
    template <typename Range2>
    operator Ranged<Range2>() const {
        return timedata::scale<Range2>(timedata::unscale<Range>(value_));
    }

    explicit operator bool() const { return value_ != 0.0f; }
    operator value_type&() { return value_; }
    operator value_type const&() const { return value_; }

    value_type& operator*() { return value_; }
    value_type const &operator*() const { return value_; }

    Ranged operator-() const { return {-value_}; }

    Ranged operator+(Ranged const& x) const { return value_ + x.value_; }
    Ranged operator-(Ranged const& x) const { return value_ - x.value_; }
    Ranged operator*(Ranged const& x) const { return value_ * x.value_; }
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

}  // timedata
