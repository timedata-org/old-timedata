#pragma once

namespace timedata {
namespace converter {

/** Loads a converter for a specific C++ type into the list of converters,
    returning the string name of the sample type.

    Please note that this isn't thread-safe so you need to make sure that this
    is always called on a single thread, quite likely the thread that loads the
    Python extension.
*/
template <typename Sample>
std::string loadConverter();


/** PointerAsInt is just a mnemonic typedef to indicate that the integer
    in question is actually some pointer, encoded.

    Because we're communicating between two different Python objects, we can't
    pass C++ pointers between different Sample implementations!

    We get around this by encoding the pointers as uint64_t when they are given
    to Python and then decoding them when we get the pointer back into C++.

    Reasonable care must be taken to avoid the usual issues involving type
    punning.  In this case, the underlying representation of all the types we're
    currently sending around are exactly the same, three 32-bit floating point
    numbers, which makes things easier.
*/
using PointerAsInt = uint64_t;

/** Casts a reference to an integer. */
template <typename T>
PointerAsInt referenceToInteger(T const& t) {
    return reinterpret_cast<uint64_t>(&t);
}

/** Casts an integer to a reference.
    This function has undefined behavior if:
    * The value t did not come from a call to referenceToInteger<T> for
      the same type T, or
    * The object at that original address has been deleted or moved.
*/
template <typename T>
T& integerToReference(PointerAsInt t) {
    return *reinterpret_cast<T*>(t);
}

/** Converts samples from one model to another, returning true on success.

    Sample conversion is only guaranteed to have a reasonable result on in-band
    signals.  For out-of-band values, the only guarantee you get is that it
    won't crash and it will return some value - there are no guarantees that
    this operation is one-to-one or onto or invertible or anything else.

    For in-band conversions, convertSample is guaranteed to give results that
    are as invertible as possible, given that not every color model directly
    maps onto every part of every other one...
*/
template <typename T>
bool convertSample(PointerAsInt inPtr, std::string const& inputModel, T& out);

template <typename Model, typename RangeIn, typename RangeOut>
void convertSample(Sample<Model, RangeIn> const& in,
                   Sample<Model, RangeOut>& out) {
    for (size_t i = 0; i < out.size(); ++i)
        out[i] = in[i];
}

/** Convert between normalized versions of two different models. */
template <typename ModelIn,
          typename ModelOut,
          typename = enable_if_t<not std::is_same<ModelIn, ModelOut>::value>>
void convertSample(Sample<ModelIn> const& in, Sample<ModelOut>& out);

template <typename ModelIn,
          typename ModelOut,
          typename RangeIn,
          typename = enable_if_t<not std::is_same<ModelIn, ModelOut>::value>>
void convertSample(Sample<ModelIn, RangeIn> const& in, Sample<ModelOut>& out) {
    Sample<ModelIn> normalIn;
    convertSample(in, normalIn);
    convertSample(normalIn, out);
}

template <typename ModelIn,
          typename ModelOut,
          typename RangeOut,
          typename = enable_if_t<not std::is_same<ModelIn, ModelOut>::value>>
void convertSample(Sample<ModelIn> const& in, Sample<ModelOut, RangeOut>& out) {
    Sample<ModelOut> normalOut;
    convertSample(in, normalOut);
    convertSample(normalOut, out);
}

} // converter
} // timedata
