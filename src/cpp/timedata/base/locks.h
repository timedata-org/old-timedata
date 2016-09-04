#pragma once

#include <mutex>

namespace timedata {

template <typename Mutex>
struct LockTraits {
};

template <>
struct LockTraits<std::mutex> {
    using Lock = std::unique_lock;
};

template <typename Mutex>
using LockType = typename LockTraits<Mutex>::Lock;

template <typename Mutex>
LockType<Mutex> locker(Mutex const& mutex) {
    return {mutex};
}

template <typename Mutex = std::mutex>
class Locker {
  public:
    using Lock = LockType<Mutex>;

    template <typename Function>
    void operator()(Function f) const {
        auto lock = (*this)();
        f();
    }

    Lock operator()() const {
        return {mutex_};
    }

  private:
    Mutex mutex_;
};

} // namespace
