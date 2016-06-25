#pragma once

#include <string>

namespace timedata {

/** Log items to std::err separated by spaces. */
template <typename ... Args>
void log(Args&& ...);

/** Join items into a string. */
template <typename ... Args>
std::string join(Args&& ...);

/** Join items to a string separated by spaces. */
template <typename ... Args>
std::string joinSpace(Args&& ...);

} // timedata
