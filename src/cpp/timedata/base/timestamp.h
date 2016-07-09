#pragma once

#include <string>

namespace timedata {

inline std::string compileTimestamp() {
#ifdef WINDOWS
    return "not implemented";
#else
    return COMPILE_TIMESTAMP;
#endif
}

inline std::string gitTags() {
#ifdef WINDOWS
    return "not implemented";
#else
    return GIT_TAGS;
#endif
}

inline std::string optimizationFlags() {
#ifdef WINDOWS
    return "not implemented";
#else
    return OPTIMIZATION_FLAGS;
#endif
}

} // timedata
