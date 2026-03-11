#include <bits/stdc++.h>
using namespace std;

/**
 * Implement a vector from scratch
 * 
 * Basic Goals:
 * - push_back, pop_back, size, capacity
 * - operator[], at (with bounds checking), front, back
 * - reserve, clear, growth & reallocation logic (2x capacity)
 * - copy constructor/assignment, move constructor/assignment
 * - 
 * 
 * Extended Goals:
 * - standard compliant
 * - placement new
 * - exception safety (when resizing the vector)
 * - templates implementation
 * - decoupling memory allocation from object lifetime
 * - checking if the move constructor is nothrow
 * - using scope guards to undo changes in the case an exception is thrown by a copy constructor
 * 
 * look up in STL guides how vector actually does this under the hood
 */

template<typename T>
class Vector {
public:
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    Vector(size_t count, const T& value = T()) 
        : data_(nullptr), size_(0), capacity_(0) 
    {
        if (count > 0) {
            // ::operator new (allocates memory)
            data_ = (T*)::operator new(count * sizeof(T));
            capacity_ = count * 2;

            for (size_t i = 0; i < count; ++i) {
                // data_ + i is automatic pointer arithmetics
                new (data_ + i) T(value);   // placement new (constructing)
                ++size_;                    // increment after each successful construction
            }
        }
    }

    void push_back(const T& value) {
        if (size_ == capacity_) grow();

        new (data_ + size_) T(value);
        ++size_;
    }

    void push_back(T&& value) {
        if (size_ == capacity_) grow();

        new (data_ + size_) T(std::move(value));
        ++size_;
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
            data[size_].~T();
        }
    }

    ~Vector() {
        // RAII: Releases the Acquired resource
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }

        // Now free
        ::operator delete(data_);
    }
private:
    T* data_;
    size_t size_;
    size_t capacity_;

    // x2 capacity
    void grow() {
        size_t new_capacity = (capacity_ == 0) ? 2 : capacity_ * 2;

        T* new_data = static_cast<T*>(::operator new(new_capacity * sizeof(T)));

        for (size_t i = 0; i < size_; ++i) {
            new (new_data + i) T(std::move(data_[i]));
            data_[i].~T();
        }

        size_t moved = 0;
        try {
            for (size_t i = 0; i < size_; ++i) {
                new (new_data + i) T(std::move(data_[i]));
            }
        } catch (...) {
            for (size_t i = 0; i < moved; ++i) {
                new_data[i].~T();
            }
            ::operator delete(new_data);
            throw std::bad_alloc;
        }

        // RAII: operator
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }

        // Now free after everything cleaned up
        ::operator delete(data_);

        // data_ points to new_data
        // no need to call destructor on new_data
        data_ = new_data;
        capacity_ = new_capacity;
    }
};

int main() {
    Vector<char>* v = new Vector(0, 'a');
    auto v1 = new Vector<char>();
}
