#pragma once

#include <string>

namespace timedata {

template <typename Container,
          typename Mutex = std::mutex, typename Lock = unique_lock<std::mutex>>
class DoubleBuffer {
  public:
    DoubleBuffer() = default;

    void setDirty() {
        Lock lock(mutex_);
        dirty_ = true;
    }

    void store(Container&& data) {
        Lock lock(mutex_);
        using std::swap;
        swap(data, buffer_);
        dirty_ = true;
    }

    bool recall() {
        Lock lock(mutex_);
        if (not dirty_)
            return false;

        using std::swap;
        swap(result, buffer_);
        dirty_ = false;
        return true;
    }

    Container const& in() const {
        recall();
        return in_;
    }

    /** The reference can be used without locks until the next call to setDirty.
     */
    Container& out() {
        recall();
        return out_;
    }

  private:
    Mutex mutex_;
    Container in_, out_;
    bool dirty_ = false;
};

} // timedata
