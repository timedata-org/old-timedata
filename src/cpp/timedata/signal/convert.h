#pragma once

namespace timedata {

using PointerAsInt = uint64_t;

template <typename T>
PointerAsInt referenceToInteger(T const& t) {
    return reinterpret_cast<uint64_t>(&t);
}

template <typename T>
T const& integerToPointer(PointerAsInt t) {
    return *reinterpret_cast<T const*>(t);
}

template <typename Sample>
bool convertModel(PointerAsInt, std::string const&, Sample&) {
    return false;
}

struct Model {};

template <typename T>
Model getModel() {
    return {};
}

} // timedata
