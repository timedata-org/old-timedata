#pragma once

#include <tdsp/base/string.h>

namespace tdsp {

// String utilities.

inline
std::string replace(std::string subject,
                    std::string const& search,
                    std::string const& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}

inline
void lower(std::string* subject) {
    for (auto& ch: *subject)
        ch = tolower(ch);
}

// Return a float as "x.xxx".
inline
std::string toString(float f) {
    f = std::min(1.0f, std::max(0.0f, f));
    std::string result;
    result.resize(5);
    result.resize(sprintf(&result.front(), "%.3f", f));
    return result;
}

// Return a float as "xx.x or 100.0".
inline
std::string toPercent(float g) {
    auto f = roundf(std::min(1.0f, std::max(0.0f, g)) * 1000.0f) / 10.0f;
    std::string result;
    result.resize(5);
    result.resize(sprintf(&result.front(), "%.1f", f));
    if (result.find(".0") != std::string::npos)
        result = result.substr(0, result.size() - 2);
    return result;
}

}  // namespace tdsp
