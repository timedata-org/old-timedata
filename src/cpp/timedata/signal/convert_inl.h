#pragma once

#include <functional>
#include <map>
#include <string>

#include <timedata/base/className.h>
#include <timedata/base/deletable.h>
#include <timedata/base/join_inl.h>
#include <timedata/color/models/rgb.h>
#include <timedata/color/models/hsv.h>
#include <timedata/signal/convert.h>

namespace timedata {
namespace converter {

template <typename Model, typename RangeIn, typename RangeOut>
void convertSample(Sample<Model, RangeIn> const& in,
                   Sample<Model, RangeOut>& out) {
    for (size_t i = 0; i < out.size(); ++i)
        out[i] = in[i];
}

template <typename ModelIn,
          typename ModelOut,
          typename RangeIn,
          typename = enable_if_t<not std::is_same<ModelIn, ModelOut>::value>,
          typename = enable_if_t<not std::is_same<RangeIn, Normal<>>::value>>
void convertSample(Sample<ModelIn, RangeIn> const& in, Sample<ModelOut>& out) {
    Sample<ModelIn> normalIn;
    convertSample(in, normalIn);
    convertSample(normalIn, out);
}

template <typename ModelIn,
          typename ModelOut,
          typename RangeOut,
          typename = enable_if_t<not std::is_same<ModelIn, ModelOut>::value>,
          typename = enable_if_t<not std::is_same<RangeOut, Normal<>>::value>>
void convertSample(Sample<ModelIn> const& in, Sample<ModelOut, RangeOut>& out) {
    Sample<ModelOut> normalOut;
    convertSample(in, normalOut);
    convertSample(normalOut, out);
}

/** The problem: there are many different sample models, and some of them are
    interconvertible but some will not be.  How do we represent this in C++ in
    such a way as to be usable from Python?

    Making converters for each pair of models is not feasible as the number of
    pairs of models grows as the square of the number of models.

    So for each model, we define a "normal" model, and each new model must only
    provide two conversion functions: to and from the normal model.

    These conversion functions need to be "very nearly round-trip" - in other
    words, if you convert back and forth ("round-trip") between any pair of
    models you should get what you started with - "very nearly" because with all
    floating point arithmetic, it's not possible to do any calculations with
    perfect precision.

    However, a color model based on 8-bit integers is _not_ round-trip with a
    floating point model, because of the tremendous loss of precision.

    For version 1.0, we in fact only have one normal model, ColorRGB and all
    samples are interconvertible.  I don't generally write for features not yet
    implemented but I think that if I had assumed that all samples were the same
    interconvertible family, I'd have had big problems later...

*/

/* Even though we're converting between a lot of different types, all this
   interface has to be uniform so we can put it into a single table.

   So we hide the intermediate.
*/
struct Converter {
    using From = Ptr<Deletable> (*)(PointerAsInt);
    using To = void (*)(Deletable const&, PointerAsInt outPtr);

    std::string name;
    From from;
    To to;
    Converter const* normal; // nullptr means "this is the normal form".
};

using Converters = std::map<std::string, Converter const*>;

/** Get the singleton list of converters. */
Converters& converters();

bool canConvert(Converter const&, Converter const&);

template <typename Sample>
Converter const& getConverterByType();

template <typename Sample>
std::string loadConverter() {
    auto name = className<Sample>();
    if (converters().find(name) == converters().end())
        converters()[name] = &getConverterByType<Sample>();
    return name;
}

template <typename T>
bool convertSampleCython(PointerAsInt inPtr,
                         std::string const& modelName, T& out) {
    auto i = converters().find(modelName);
    if (i == converters().end()) {
        log("Couldn't find converter", modelName);
        return false;
    }

    auto& to = getConverterByType<T>();
    auto& from = *(i->second);
    if (not canConvert(to, from)) {
        log("Did not share common normal", modelName, className<T>());
        return false;
    }

    auto outPtr = referenceToInteger(out);
    to.to(*from.from(inPtr), outPtr);
    return true;
}

inline Converters& converters() {
    static Converters CONVERTERS;
    return CONVERTERS;
}

inline bool canConvert(Converter const& x, Converter const& y) {
    return (&x == &y) or
           (&x == y.normal) or
           (&y == x.normal) or
           (x.normal and (x.normal == y.normal));
}

template <typename Sample>
Ptr<Deletable> convertFrom(PointerAsInt p) {
    auto& in = integerToReference<Sample const>(p);
    auto out = makeWrapper<NormalType<Sample>>();
    convertSample(in, out->value);
    return std::move(out);
}

template <typename Sample>
void convertTo(Deletable const& input, PointerAsInt outPtr) {
    auto& out = integerToReference<Sample>(outPtr);
    if (auto in = unwrap<NormalType<Sample>>(input))
        convertSample(*in, out);
    else
        log("Horrible programmer error", className<Sample>());
}

template <typename Sample>
Converter const& getConverterByType();

template <typename Sample>
Converter makeConverterByType() {
    using Normal = NormalType<Sample>;

    auto name = className<Sample>();
    auto isNormal = std::is_same<Normal, Sample>::value;
    auto normal = isNormal ? nullptr : &getConverterByType<Normal>();

    return {name, &convertFrom<Sample>, &convertTo<Sample>, normal};
}

template <typename Sample>
Converter const& getConverterByType() {
    static const auto c = makeConverterByType<Sample>();
    return c;
}

} // converter
} // timedata
