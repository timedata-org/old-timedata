#pragma once

#include <string>
#include <vector>

#include <tdsp/color/color.h>

namespace tdsp {

using ColorList = std::vector<Color>;

template <typename T>
std::vector<T> duplicate(std::vector<T> const&, size_t count);

template <typename T>
void reverse(std::vector<T>&);

std::string toString(ColorList const&);

template <typename T>
std::vector<T> sliceVector(
    std::vector<T> const& in, int begin, int end, int step);

template <typename T>
bool sliceIntoVector(std::vector<T> const& in, std::vector<T>& out,
                     int begin, int end, int step);

template <typename Function>
void forEachColorComponent(ColorList& colors, Function f);

template <typename Function>
void forEachColorComponent(ColorList const& in, ColorList& out, Function f);

void absColor(ColorList& out);
void negateColor(ColorList& out);
void invertColor(ColorList& out);

void addInto(float f, ColorList& out);
void addInto(ColorList const& in, ColorList& out);

void divideInto(float f, ColorList& out);
void divideInto(ColorList const& in, ColorList& out);

void multiplyInto(float f, ColorList& out);
void multiplyInto(ColorList const& in, ColorList& out);

void powInto(float f, ColorList& out);
void powInto(ColorList const& in, ColorList& out);

void rdivideInto(float f, ColorList& out);
void rdivideInto(ColorList const& in, ColorList& out);

void rpowInto(float f, ColorList& out);
void rpowInto(ColorList const& in, ColorList& out);

void rsubtractInto(float f, ColorList& out);
void rsubtractInto(ColorList const& in, ColorList& out);

void subtractInto(float f, ColorList& out);
void subtractInto(ColorList const& in, ColorList& out);

void minInto(float f, ColorList& out);
void minInto(ColorList const& in, ColorList& out);

void maxInto(float f, ColorList& out);
void maxInto(ColorList const& in, ColorList& out);

} // tdsp
