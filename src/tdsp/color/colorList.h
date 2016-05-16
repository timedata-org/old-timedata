#pragma once

#include <string>
#include <vector>

#include <tdsp/base/rotate.h>
#include <tdsp/color/color.h>

namespace tdsp {

using ColorListBase = std::vector<Color>;

#if 1

using ColorList = ColorListBase;

#else

struct ColorList : public ColorListBase {
    ColorList() {
        log("creating");
    }

    ColorListBase& operator=(ColorListBase const&x) {
        log("copying");
        ColorListBase::operator=(x);
        return *this;
    }
};

#endif

ColorList duplicate(ColorList const&, size_t count);

void reverse(ColorList&);

std::string toString(ColorList const&, Base base = Base::normal);

ColorList sliceVector(
    ColorList const& in, int begin, int end, int step);

bool sliceIntoVector(ColorList const& in, ColorList& out,
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
