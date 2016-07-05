#pragma once

#include <map>
#include <string>

#include <timedata/signal/convert.h>
#include <timedata/base/deletable.h>
#include <timedata/base/join.h>

namespace timedata {
namespace converter {

struct Converter {
    /** Abstract base class with the actual implementation. */
    struct Convert : Deletable {
        /** Convert from this model to the base type, returned as a Deleteable.
            (because this is a facade for a lot of disparate classes which are
            keeping different types of data behind the scenes).
        */
        virtual Deletable::Ptr from(PointerAsInt fromPtr) const = 0;

        /** Convert from the base type to this model.
            Returns false if the DeletablePtr can't be upcast to the correct actual
            type for this model. */
        virtual bool to(PointerAsInt toPtr, DeletablePtr&& from) const = 0;
    };

    using ConvertPtr = std::unique_ptr<Impl>;

    std::string name;
    ConvertPtr convert;
    Converter const* base; // nullptr means "this is the base".

    Converter(std::string const& n, ConvertPtr&& c,
              Converter const* b = nullptr)
            : name(n), convert(std::move(c)), base(b) {
    }
};

using Converters = std::map<std::string, Converter>;

// Singleton.
inline Converters& converters() {
    static Converters CONVERTERS;
    return CONVERTERS;
}

inline void addConverter(Converter&& c) {
    if (converters().count(c.name))
        log("Converter", c.name, "added twice.");
    else
        converters()[c.name] = std::move(c);
}

template <typename Model>
Converter& make() {

};


/*
auto timedata_color_rgb = timedata::converter:make<timedata::color::RGB>();
*/
struct Registrar {
    Registrar(std::string const& name,

template <typename Impl>
inline void addBaseConverter(std::string name) {
    addConverter({name, std::make_unique<Impl>(), nullptr});
}

template <typename Impl>
inline void addConverter(std::string name, Converter const& base) {
    addConverter({name, std::make_unique<Impl>(), &base});
}


template <typename Sample>
std::string convertConverter(PointerAsInt fromPtr, std::string const& converter,
                             Sample& sample) {
    auto toName = className<typename Sample::model_type>();
    auto f = converters().find(fromName),
         t = converters().find(toName);

    if (f == converters().end())
        return "Can't find converter " + fromName;
    if (t == converters().end())
        return "Can't find converter " + toName;

    auto& fromConverter = f.second;
    auto& toConverter = t.second;

    if (&fromConverter.base != &toConverter.base) {
        return "Converter " + toName + " and converter " + fromName +
                " have different base converters: " + fromConverter.base.name + " and " +
                toConverter.base.name;
    }
    auto toPtr = pointerToInteger(sample);
    if (not toConverter.to(toPtr, fromConverter.from(fromPtr)))  // Can't happen.
        return "Internal error converting from " + fromName + " to " + toName;
    return "";
}

} // converter
} // timedata
