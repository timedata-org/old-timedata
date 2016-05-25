#pragma once

#include <stdexcept>
#include <tada/base/join_inl.h>

namespace tada {

struct Exception : std::runtime_error {
    template <typename ... Args>
    Exception(Args&& ... args)
            : std::runtime_error(joinSpace(std::forward<Args>(args)...)) {
    }
};

template <typename ... Args>
void throwIf(bool cond, Args&& ... args) {
    if (cond)
        throw Exception(std::forward<Args>(args)...);
}

template <typename X, typename Y, typename ... Args>
void throwIfEQ(X x, Y y, Args&& ... args) {
    if (x == y)
        throw Exception(x, "==", y, std::forward<Args>(args)...);
}

template <typename X, typename Y, typename ... Args>
void throwIfNE(X x, Y y, Args&& ... args) {
    if (x != y)
        throw Exception(x, "!=", y, std::forward<Args>(args)...);
}

template <typename X, typename Y, typename ... Args>
void throwIfLT(X x, Y y, Args&& ... args) {
    if (x < y)
        throw Exception(x, "<", y, std::forward<Args>(args)...);
}

template <typename X, typename Y, typename ... Args>
void throwIfLE(X x, Y y, Args&& ... args) {
    if (x <= y)
        throw Exception(x, "<=", y, std::forward<Args>(args)...);
}

template <typename X, typename Y, typename ... Args>
void throwIfGT(X x, Y y, Args&& ... args) {
    if (x > y)
        throw Exception(x, ">", y, std::forward<Args>(args)...);
}

template <typename X, typename Y, typename ... Args>
void throwIfGE(X x, Y y, Args&& ... args) {
    if (x >= y)
        throw Exception(x, ">=", y, std::forward<Args>(args)...);
}

template <typename X, typename ... Args>
void throwIfEmpty(X const& x, Args&& ... args) {
    if (x.empty())
        throw Exception("Empty collection:", std::forward<Args>(args)...);
}

} // tada

#define THROW(...) throw Exception(__FILE__, __LINE__, __VA_ARGS__)
#define THROW_IF(C, ...) throwIf(C, #C, __FILE__, __LINE__, __VA_ARGS__)
#define THROW_IF_EQ(X, Y, ...) throwIfEQ(X, Y, __FILE__, __LINE__, __VA_ARGS__)
#define THROW_IF_NE(X, Y, ...) throwIfNE(X, Y, __FILE__, __LINE__, __VA_ARGS__)
#define THROW_IF_LT(X, Y, ...) throwIfLT(X, Y, __FILE__, __LINE__, __VA_ARGS__)
#define THROW_IF_LE(X, Y, ...) throwIfLE(X, Y, __FILE__, __LINE__, __VA_ARGS__)
#define THROW_IF_GT(X, Y, ...) throwIfGT(X, Y, __FILE__, __LINE__, __VA_ARGS__)
#define THROW_IF_GE(X, Y, ...) throwIfGE(X, Y, __FILE__, __LINE__, __VA_ARGS__)
#define THROW_IF_EMPTY(C, ...) throwIfEmpty(C, __FILE__, __LINE__, __VA_ARGS__)
