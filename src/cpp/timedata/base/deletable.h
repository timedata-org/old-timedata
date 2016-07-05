#pragma once

#include <timedata/base/make_unique.h>

namespace timedata {

struct Deletable {
    virtual ~Deletable() {}

    using Ptr = std::unique_ptr<Deletable>();
};

template <typename T>
struct Wrapper : Deletable {
    using value_type = T;
    using ptr_type = std::unique_ptr<Wrapper>();

    value_type value;

    Wrapper(value_type&& w) : value(std::move(w)) {}
};

template <typename T>
typename Wrapper<T>::ptr_type makeWrapper(T&& w) {
    return std::make_unique<Wrapper<T>>(std::move(w));
}

} // timedata
