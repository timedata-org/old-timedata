#pragma once

#include <strstream>
#include <typeinfo>

namespace tdsp {
namespace detail {

using Expander = int[];

template <typename Stream, typename T>
void appendTo(Stream& s, T const& t) {
    s << t;
}

template <typename Stream>
void appendTo(Stream& s, char const* t) {
    s << t;
}

template <typename Stream, typename T>
void spaceAppendTo(Stream& s, T const& t) {
    s << " ";
    appendTo(s, t);
}

inline std::string joinSpace() {
    return {};
}

template <typename Arg>
std::string joinSpace(Arg&& arg) {
    std::strstream ss;
    ss << arg;
    return ss.str();
}

template <typename Arg, typename ... Args>
std::string joinSpace(Arg&& arg, Args&&... args) {
    std::strstream ss;
    ss << arg;
    (void) detail::Expander{
        (spaceAppendTo(ss, std::forward<Args>(args)), void(), 0) ... };
    return ss.str();
}

inline
void print() {
    std::cerr << '\n';
}

template <typename Arg>
void print(Arg&& arg) {
    std::cerr << arg << '\n';
}

template <typename Arg, typename ... Args>
void log(Arg&& arg, Args&& ... args) {
    std::cerr << arg;
    (void) detail::Expander{(spaceAppendTo(
        std::cerr, std::forward<Args>(args)), void(), 0) ... };
    std::cerr << '\n';
}

} // detail

inline
std::string join() {
    return {};
}

template <typename ... Args>
std::string join(Args&& ... args) {
    std::strstream ss;
    (void) detail::Expander{(detail::appendTo(
        ss, std::forward<Args>(args)), void(), 0) ... };
    return ss.str();
}

template <typename ... Args>
void log(Args&& ... args) {
    detail::log(std::forward<Args>(args) ...);
}

template <typename ... Args>
std::string joinSpace(Args&& ... args) {
    return detail::joinSpace(std::forward<Args>(args) ...);
}

} // tdsp
