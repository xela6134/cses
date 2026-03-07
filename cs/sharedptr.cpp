#include <bits/stdc++.h>
using namespace std;

using namespace std;

template <typename T>
class SharedPointer {
public:
    // Constructor (Disallow implicit construction)
    explicit SharedPointer(T* ptr = nullptr)
        : data(ptr), refCount(ptr ? new atomic<int>(1) : nullptr) {}

    // Copy constructor — share ownership
    SharedPointer(const SharedPointer& other) 
        : data(other.data), refCount(other.refCount) {
        if (refCount) (*refCount)++;
    }

    // Copy assignment operator
    SharedPointer& operator=(const SharedPointer& other) {
        if (this == &other) return *this;  // self-assignment guard
        release();                         // drop current ownership
        data     = other.data;
        refCount = other.refCount;
        if (refCount) (*refCount)++;
        return *this;
    }

    // Move constructor — steal ownership, leave other empty
    SharedPointer(SharedPointer&& other) noexcept
        : data(other.data), refCount(other.refCount) {
        other.data     = nullptr;
        other.refCount = nullptr;
        // NO increment — we're transferring, not sharing
    }

    // Move assignment operator
    SharedPointer& operator=(SharedPointer&& other) noexcept {
        if (this == &other) return *this;
        release();                  // drop what we currently own
        data     = other.data;
        refCount = other.refCount;
        other.data     = nullptr;   // leave other in valid empty state
        other.refCount = nullptr;
        return *this;
    }

    // Destructor
    ~SharedPointer() { release(); }

    // Dereference
    T& operator*()  const { return *data; }
    T* operator->() const { return data;  }

    int use_count() const { return refCount ? refCount->load() : 0; }
    T*  get()       const { return data; }

private:
    T* data;
    atomic<int>* refCount;

    void release() {
        if (!refCount) return;
        if (--(*refCount) == 0) {
            delete data;
            delete refCount;
        }
        data = nullptr;
        refCount = nullptr;
    }
};
