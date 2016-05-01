#pragma once

#include <functional>

#include <tdsp/Fcolor.h>

namespace tdsp {
namespace color {

typedef std::function<float(float)> FloatFunction;
FloatFunction makeFunction(std::string const&);

class CTransform {
  public:
    virtual ~CTransform() {}
    virtual float apply(float x) const = 0;
    virtual float inverse(float x) const = 0;
};

CTransform* makeTransform(const std::string&);

std::vector<std::string> getTransformNames();

inline float apply(FloatFunction const& f, float x) { return f(x); }
inline bool empty(FloatFunction const &f) { return !f; }

}  // namespace color
}  // namespace tdsp
