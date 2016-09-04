#pragma once

#include <timedata/base/base.h>

namespace timedata {

template <typename T>
using Ptr = std::unique_ptr<T>;

struct Deletable {
    virtual ~Deletable() {}
};

template <typename T>
struct Wrapper : Deletable {
    using value_type = T;
    value_type value;

    Wrapper() {}
    Wrapper(value_type&& w) : value(std::move(w)) {}
};

template <typename T>
Ptr<Wrapper<T>> makeWrapper() {
    return std::make_unique<Wrapper<T>>();
}

template <typename T>
Ptr<Wrapper<T>> makeWrapper(T const& w) {
    return std::make_unique<Wrapper<T>>(w);
}

template <typename T>
Ptr<Wrapper<T>> makeWrapper(T&& w) {
    return std::make_unique<Wrapper<T>>(std::move(w));
}

template <typename T>
const T* unwrap(Deletable const& wrapped) {
    if (auto d = dynamic_cast<Wrapper<T> const*>(&wrapped))
        return &d->value;
    return nullptr;
}

} // timedata
