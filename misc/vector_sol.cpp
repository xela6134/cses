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
            data_ = static_cast<T*>(::operator new(count * sizeof(T)));
            capacity_ = count * 2;

            for (size_t i = 0; i < count; ++i) {
                // data_ + i is automatic pointer arithmetics
                // T(value) is copy constructor
                new (data_ + i) T(value);   // placement new (constructing)
                ++size_;                    // increment after each successful construction
            }
        }
    }

    Vector(const Vector& other) : data_(nullptr), size_(0), capacity_(0) {
        data_ = static_cast<T*>(::operator new(other.size_ * sizeof(T)));
        capacity_ = other.capacity_;

        for (size_t i = 0; i < other.size_; ++i) {
            new (data_ + i) T(other.data_[i]);

            // In case the memory allocation throws,
            // we just increment size one by one
            ++size_;
        }
    }

    Vector& operator=(const Vector& other) {
        // Cleanup existing
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }

        ::operator delete(data_);

        // Allocate new
        data_ = static_cast<T*>(::operator new(other.size_ * sizeof(T)));
        size_ = other.size_;
        capacity_ = other.capacity_;

        for (size_t i = 0; i < other.size_; ++i) {
            new (data_ + i) T(other.data_[i]);
        }

        return *this;
    }

    Vector(Vector&& other) noexcept 
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    Vector& operator=(Vector&& other) noexcept {
        // Cleanup existing
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }

        ::operator delete(data_);

        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        return *this;
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

    // Need to give a reference if we want to modify the whole thing
    T& operator[](size_t index) {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    // Need both non-const and const
    const T& operator[](size_t index) const {
        return data_[index];
    }

    T& at(size_t index) {
        return data_[index];
    }

    const T& at(size_t index) const {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    void clear() {
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }
        size_ = 0;

        // ::operator delete(data_);
        // Not a good idea to do reallocation from scratch 
        // (even if I allocate 100k elements and clear it all, high chances are im gonna reallocate 100k)
    }

    // TODO: Revision later
    void shrink_to_fit() {
        if (size_ == capacity_) return;

        T* new_data = static_cast<T*>(::operator new(size_ * sizeof(T)));

        for (size_t i; i < size_; ++i) {
            new (new_data + i) T(std::move(data_[i]));
        }

        // 3 and 4 come in pairs
        // Step 3
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }

        // Step 4
        ::operator delete(data_);

        data_ = new_data;
        capacity_ = size_;
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
