#pragma once

#include <string>
#include <vector>

#include <tdsp/base/rotate.h>
#include <tdsp/color/color.h>

namespace tdsp {

using ColorListBase = std::vector<Color>;

struct ColorList : public ColorListBase {
    void setColor(size_t i, float r, float g, float b) {
        (*this)[i] = {{r, g, b}};
    }

    // Returns negative for a bad key.
    bool fixKey(int& key) const {
        if (key < 0)
            key += size();
        return key >= 0 and key < size();
    }

    size_t getSizeOf() const {
        return sizeof(ColorList) + size() * sizeof(Color);
    }

    using ColorListBase::ColorListBase;
};

ColorList duplicate(ColorList const&, size_t count);

void reverse(ColorList&);

std::string toString(ColorList const&, Base base = Base::normal);

ColorList sliceVector(
    ColorList const& in, int begin, int end, int step);

bool sliceIntoVector(ColorList const& in, ColorList& out,
                     int begin, int end, int step);

template <typename Function>
void forEachColorComponent(ColorList const& in, ColorList& out, Function f);

void absColor(ColorList& out);
void ceilColor(ColorList& out);
void floorColor(ColorList& out);
void invertColor(ColorList& out);
void negateColor(ColorList& out);  // rename to neg
void roundColor(ColorList& out);
void truncColor(ColorList& out);

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

template <typename X, typename Y>
void addOver(X const& x, Y const& y, ColorList& out);

template <typename X, typename Y>
void divOver(X const& x, Y const& y, ColorList& out);

template <typename X, typename Y>
void mulOver(X const& x, Y const& y, ColorList& out);

template <typename X, typename Y>
void powOver(X const& x, Y const& y, ColorList& out);

template <typename X, typename Y>
void subOver(X const& x, Y const& y, ColorList& out);

void hsvToRgbInto(ColorList&, Base);
void rgbToHsvInto(ColorList&, Base);

} // tdsp
