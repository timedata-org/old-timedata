#pragma once

#include <string>

namespace tada {

inline std::string compileTimestamp() {
    return COMPILE_TIMESTAMP;
}

inline std::string gitTags() {
    return GIT_TAGS;
}

} // tada
