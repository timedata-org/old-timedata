#pragma once

#include <string>

namespace timedata {

template <typename T>
std::string className();

template <typename T>
std::string className(T const&) {
    return className<T>();
}

}  // namespace timedata
