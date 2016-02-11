#include <math.h>

#include <map>
#include <sstream>

#include <fcolor/Transform.h>

using namespace std;

namespace fcolor {
namespace color {

typedef pair<FloatFunction, FloatFunction> FloatTransform;

namespace {

std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (getline(ss, item, delim))
        elems.push_back(item);

    return elems;
}

float const PI = 3.14159265358979f;
float const E = 2.718281828f;

float croot(float x)    { return powf(x, 1.0f / 3.0f); }
float cube(float x)     { return x * x * x; }
float identity(float x) { return x; }
float reverse(float x)  { return 1.0 - x; }
float square(float x)   { return x * x; }

float sine(float x) {
    return (1 + sinf(PI * (x - 0.5))) / 2;
}

float arcsine(float x) {
    return 0.5 + asinf(2 * x - 1) / PI;
}

float exp(float x) {
    return (expf(x) - 1) / (E - 1);
}

float log(float x) {
    return logf((E - 1) * x + 1);
}

FloatFunction mirror(FloatFunction const& f) {
    if (!f)
        return f;
    return [f] (float x) {
        if (x <= 0.5)
            return f(2 * x) / 2;

        return 1 - f(2 * (1 - x)) / 2;
    };
};

class CTransformBase : public CTransform {
  public:
    explicit CTransformBase(const FloatTransform& ft) : floatTransform_(ft) {}

    float apply(float x) const override { return floatTransform_.first(x); }
    float inverse(float x) const override { return floatTransform_.second(x); }

  private:
    FloatTransform const floatTransform_;
    // DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(CTransformBase);
    // See https://github.com/rec/fcolor/issues/512
};

class Inverse : public CTransform {
  public:
    explicit Inverse(unique_ptr<CTransform> t) : transform_(move(t)) {}

    float apply(float x) const override { return transform_->inverse(x); }
    float inverse(float x) const override { return transform_->apply(x); }

  private:
    unique_ptr<CTransform> transform_;
    DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Inverse);
};

class Compose : public CTransform {
  public:
    Compose(unique_ptr<CTransform> first, unique_ptr<CTransform> second)
            : first_(move(first)), second_(move(second)) {
    }

    float apply(float x) const override {
        return second_->apply(first_->apply(x));
    }

    float inverse(float x) const override {
        return first_->inverse(second_->inverse(x));
    }

  private:
    unique_ptr<CTransform> first_, second_;
    DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Compose);
};

unique_ptr<CTransform> compose(
    unique_ptr<CTransform> first, unique_ptr<CTransform> second) {
    if (not first.get())
        return move(second);
    if (not second.get())
        return move(first);
    return unique_ptr<CTransform>(new Compose(move(first), move(second)));
}

unique_ptr<CTransform> inverse(unique_ptr<CTransform> transform) {
    if (not transform.get())
        throw Exception("Invert cannot be the first transform.");
    return unique_ptr<CTransform>(new Inverse(move(transform)));
}

typedef std::map<std::string, FloatTransform> TransformMap;

FloatTransform power(float n) {
    return FloatTransform(
        bind(powf, placeholders::_1, n),
        bind(powf, placeholders::_1, 1 / n));
}

TransformMap makeTransforms() {
    TransformMap tm;

    tm["cube"] = power(3);
    tm["exp"] = FloatTransform(exp, log);
    tm["identity"] = FloatTransform(identity, identity);
    tm["log"] = FloatTransform(log, exp);
    tm["reverse"] = FloatTransform(reverse, reverse);
    tm["sine"] = FloatTransform(sine, arcsine);
    tm["sqrt"] = FloatTransform(sqrtf, square);
    tm["square"] = FloatTransform(square, sqrtf);

    return tm;
}

auto TRANSFORMS = makeTransforms();

unique_ptr<CTransform> getOneTransform(const std::string& name) {
    auto i = TRANSFORMS.find(name);
    if (i == TRANSFORMS.end())
        throw Exception("Can't understand transform " + name);
    return unique_ptr<CTransform>(new CTransformBase(i->second));
}

unique_ptr<CTransform> getTransform(const std::string& name) {
    unique_ptr<CTransform> result;
    bool invert = false;

    std::string token;
    for (auto i = 0; i <= name.size(); ++i) {
        auto ch = name.c_str()[i];
        if (ch and (not isspace(ch)) and (ch != '+')) {
            token.push_back(ch);
        } else if (not token.empty()) {
            if (token == "inverse") {
                if (result.get())
                    result = inverse(move(result));
                else
                    invert = true;
            } else {
                result = compose(move(result), move(getOneTransform(token)));
            }
            token.clear();
        }
    }
    if (invert)
        result = inverse(move(result));

    return move(result);
}

FloatFunction findFunction(std::string const& s, bool isInverse) {
    using Table = std::map<std::string, FloatFunction>;
    static Table const TABLE{
        {"croot", croot},
        {"cube", cube},
        {"exp", exp},
        {"identity", identity},
        {"log", log},
        {"reverse", reverse},
        {"sine", sine},
        {"sqrt", sqrtf},
        {"square", square}
    };

    static Table const INVERSE{
        {"croot", cube},
        {"cube", croot},
        {"exp", log},
        {"identity", identity},
        {"log", exp},
        {"reverse", reverse},
        {"sine", arcsine},
        {"sqrt", square},
        {"square", sqrtf}
    };

    auto& table = isInverse ? INVERSE : TABLE;

    auto i = table.find(s);
    if (i != table.end())
        return i->second;
    return {};
}

inline FloatFunction compose(
        FloatFunction const& first, FloatFunction const& second) {
    if (!(first && second))
        return first;
    return [first, second] (float x) {
        return second(first(x));
    };
}

inline FloatFunction reverse(FloatFunction const& f) {
    if (!f)
        return f;
    return [f] (float x) {
        return f(1 - x);
    };
}

FloatFunction makeOneFunction(std::string const& s) {
    auto pos = s.find('(');
    if (pos == std::string::npos)
        return findFunction(s, false);

    if (!pos || s.back() != ')')
        return {};

    auto mod = s.substr(0, pos);
    auto rem = s.substr(pos + 1, s.size() - pos - 2);
    if (mod == "inverse")
        return findFunction(rem, true);
    auto f = makeFunction(rem);
    if (!f)
        return f;
    if (mod == "mirror")
        return mirror(f);
    else if (mod == "reverse")
        return reverse(f);
    return {};
}

} // namespace

CTransform* makeTransform(const std::string& s) {
    try {
        return getTransform(s).release();
    } catch (Exception e) {
        LOG(ERROR) << e.what();
        return nullptr;
    }
}

FloatFunction makeFunction(std::string const& s) {
    auto tokens = split(s, '+');
    auto size = tokens.size();
    if (!size)
        return {};

    auto f = makeOneFunction(tokens[0]);
    for (auto i = 1; i < size; ++i)
        f = compose(makeOneFunction(tokens[i]), f);
    return f;
}

std::vector<std::string> getTransformNames() {
    std::vector<std::string> res;
    for (auto i: TRANSFORMS)
        res.push_back(i.first);
    return res;
}

}  // namespace color
}  // namespace fcolor
