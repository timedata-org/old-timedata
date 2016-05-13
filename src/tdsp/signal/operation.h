#pragma once

#include <string>
#include <vector>

#include <tdsp/color/color.h>

namespace tdsp {

struct Operation {
    enum class Unary {ABS, CLEAR, INVERT, NEGATE, size};
    enum class Commutative {ADD, MAX, MIN, MUL, size};
    enum class NonCommutative {DIV, SUB, POW, size};
};

template <typename Collection>
void operateInto(Operation::Unary, Collection&);

template <typename Collection>
void operateInto(Operation::Commutative, float x, Collection&);

template <typename Collection>
void operateInto(Operation::Commutative, Collection const& in, Collection&);


template <typename Collection>
void operateInto(Operation::NonCommutative, float x, Collection&);

template <typename Collection>
void operateInto(Operation::NonCommutative, Collection const& in, Collection&);


template <typename Collection>
void operateIntoLeft(Operation::NonCommutative, float x, Collection&);

template <typename Collection>
void operateIntoLeft(Operation::NonCommutative, Collection const& in, Collection&);


template <typename Collection>
Collection operate(Operation::Unary, Collection const&);

template <typename Collection>
Collection operate(Operation::Commutative,
                   Collection const&, Collection const&);

template <typename Collection>
Collection operate(Operation::NonCommutative,
                   Collection const&, Collection const&);

} // tdsp
