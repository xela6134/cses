#include <bits/stdc++.h>
using namespace std;

template<typename T>
class SharedPtr {
public:
    SharedPtr(T* resource) : resource_(resource), use_count_(new std::atomic<int>(1)) {}

    SharedPtr(const SharedPtr& other) : resource_(other.resource_), use_count_(other.use_count_) {
        ++(*use_count_);
    }

    SharedPtr(SharedPtr&& other) noexcept : resource_(other.resource_), use_count_(other.use_count_) {
        other.resource_ = nullptr;
        other.use_count_ = nullptr;
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this == &other) return *this;

        if (--(*use_count_) == 0) release();

        resource_ = other.resource_;
        use_count_ = other.use_count_;
        ++(*use_count_);

        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this == &other) return *this;

        if (--(*use_count_) == 0) release();

        resource_ = other.resource_;
        use_count_ = other.use_count_;
        other.resource_ = nullptr;
        other.use_count_ = nullptr;

        return *this;
    }

    int ref_count() {
        return (use_count_ == nullptr) ? 0 : *use_count_;
    }

    T& operator*() const {
        return *resource_;
    }

    T* operator->() const {
        return resource_;
    }

    ~SharedPtr() {
        if (--(*use_count_) == 0) release();
    }
private:
    T* resource_;
    std::atomic<int>* use_count_;

    void release() {
        delete resource_;
        delete use_count_;
    }
};

int main() {
    auto p1 = make_shared<int>(42);
    auto p2 = p1;
    auto p3 = p1;
    auto p4 = p1;

    cout << p1.use_count() << '\n';

    auto p5 = std::move(p1);

    cout << p1.use_count() << '\n';
    cout << p5.use_count() << '\n';

    return 0;
}
