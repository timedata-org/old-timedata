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

template <typename T>
//string convertTo(PointerAsInt input, string model, T& result) {
std::string convertTo(PointerAsInt, std::string const&, T&) {
    return "Can't do conversions yet";
}


} // timedata
