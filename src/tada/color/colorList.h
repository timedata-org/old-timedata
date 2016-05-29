#pragma once

#include <string>
#include <vector>

#include <tada/base/rotate.h>
#include <tada/color/color.h>

namespace tada {

using ColorVectorBase = std::vector<Color>;

struct ColorVector : public ColorVectorBase {
    void setColor(size_t i, float r, float g, float b) {
        (*this)[i] = {{r, g, b}};
    }

    // Returns negative for a bad key.
    bool fixKey(int& key) const {
        if (key < 0)
            key += size();
        return key >= 0 and key < int(size());
    }

    size_t getSizeOf() const {
        return sizeof(ColorVector) + size() * sizeof(Color);
    }

    using ColorVectorBase::ColorVectorBase;
};

void clearInto(ColorVector&);
void reverse(ColorVector&);
void appendInto(ColorVector const&, ColorVector&);
void duplicateInto(size_t count, ColorVector&);

std::string toString(ColorVector const&, Base base = Base::normal);

ColorVector sliceVector(
    ColorVector const& in, int begin, int end, int step);

bool sliceIntoVector(ColorVector const& in, ColorVector& out,
                     int begin, int end, int step);

template <typename Function>
void forEachColorComponent(ColorVector const& in, ColorVector& out, Function f);

void absInto(ColorVector& out);
void ceilInto(ColorVector& out);
void floorInto(ColorVector& out);
void invertColor(ColorVector& out);
void negateColor(ColorVector& out);  // rename to neg
void roundColor(ColorVector& out, uint digits);
void truncColor(ColorVector& out);

void addInto(float f, ColorVector& out);
void addInto(ColorVector const& in, ColorVector& out);

void divideInto(float f, ColorVector& out);
void divideInto(ColorVector const& in, ColorVector& out);

void multiplyInto(float f, ColorVector& out);
void multiplyInto(ColorVector const& in, ColorVector& out);

void powInto(float f, ColorVector& out);
void powInto(ColorVector const& in, ColorVector& out);

void rdivideInto(float f, ColorVector& out);
void rdivideInto(ColorVector const& in, ColorVector& out);

void rpowInto(float f, ColorVector& out);
void rpowInto(ColorVector const& in, ColorVector& out);

void rsubtractInto(float f, ColorVector& out);
void rsubtractInto(ColorVector const& in, ColorVector& out);

void subtractInto(float f, ColorVector& out);
void subtractInto(ColorVector const& in, ColorVector& out);

void minInto(float f, ColorVector& out);
void minInto(ColorVector const& in, ColorVector& out);

void maxInto(float f, ColorVector& out);
void maxInto(ColorVector const& in, ColorVector& out);

template <typename X, typename Y>
void addOver(X const& x, Y const& y, ColorVector& out);

template <typename X, typename Y>
void divOver(X const& x, Y const& y, ColorVector& out);

template <typename X, typename Y>
void mulOver(X const& x, Y const& y, ColorVector& out);

template <typename X, typename Y>
void powOver(X const& x, Y const& y, ColorVector& out);

template <typename X, typename Y>
void subOver(X const& x, Y const& y, ColorVector& out);

void hsvToRgbInto(ColorVector&, Base);
void rgbToHsvInto(ColorVector&, Base);
void appendInto(ColorVector const&, ColorVector&);
void duplicateInto(size_t count, ColorVector&);
Color maxColor(ColorVector const&);
Color minColor(ColorVector const&);

} // tada
