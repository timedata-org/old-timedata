#pragma once

#include <map>
#include <string>

#include <timedata/signal/convert.h>

namespace timedata {
namespace model {

using Models = std::map<std::string, Model>;

// Singleton.
inline Models& models() {
    static Models MODELS;
    return MODELS;
}

struct ModelDesc {
    std::string name;
    std::function x;
};


template <typename Sample>
std::string convertModel(uint64_t pointer, std::string const& model,
                         float start, float range, Sample& sample) {
    auto toName = className<typename Sample::model_type>();
    auto f = models().find(fromName);
    if (f == models().end())
        return "Can't find model " + fromName;

    auto f = models().find(toName);
    if (t == models().end())
        return "Can't find model " + toName;

    auto& fromModel = f.second;
    auto& toModel = t.second;
    if (&fromModel.base != &toModel.base) {
        return "Model " + toName + " and model " + fromName +
                " have different base models: " + fromModel.base.name + " and " +
                toModel.base.name;
    }
    auto toPtr = pointerToInteger(sample);


}

} // model

} // timedata
