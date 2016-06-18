#pragma once

#include <string>

namespace tada {

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

} // tada
