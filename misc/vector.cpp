#include <bits/stdc++.h>
using namespace std;

/**
 * Implement a vector from scratch
 * 
 * Basic Goals:
 * 1. push_back, pop_back, size, capacity
 * 2. operator[], at (with bounds checking), front, back
 * 3. reserve, clear, growth & reallocation logic (2x capacity)
 * 4. copy constructor/assignment, move constructor/assignment
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

    Vector(size_t count) : size_(0), capacity_(count) {
        data_ = static_cast<T*>(::operator new(count * sizeof(T)));
        size_t i = 0;

        try {
            for (; i < count; ++i) {
                new (data_ + i) T();
            }

            size_ = count;
        } catch (...) {
            for (size_t j = 0; j < i; ++j) {
                data_[j].~T();
            }

            ::operator delete(data_);

            data_ = nullptr;
            capacity_ = 0;

            throw;
        }
    }

    Vector(size_t count, const T& value) : size_(0), capacity_(count) {
        data_ = static_cast<T*>(::operator new(count * sizeof(T)));
        size_t i = 0;

        try {
            for (; i < count; ++i) {
                new (data_ + i) T(value);
            }

            size_ = count;
        } catch (...) {
            for (size_t j = 0; j < i; ++j) {
                data_[j].~T();
            }

            ::operator delete(data_);

            data_ = nullptr;
            capacity_ = 0;

            throw;
        }
    }

    // vector<int> a(b); b -> a
    Vector(const Vector& other) : data_(nullptr), size_(0), capacity_(other.capacity_) {
        data_ = static_cast<T*>(::operator new(other.capacity_ * sizeof(T)));

        size_t i = 0;
        try {
            for (; i < other.size_; ++i) {
                new (data_ + i) T(other.data_[i]);
            }

            size_ = other.size_;
        } catch (...) {
            for (size_t j = 0; j < other.size_; ++j) {
                data_[j].~T();
            }

            ::operator delete(data_);
        }
    }

    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;

        // copy construct (if this throws, *this is untouched)
        Vector temp(other);

        std::swap(data_, temp.data_);
        std::swap(size_, temp.size_);
        std::swap(capacity_, temp.capacity_);

        return *this;

        // // 1. Wipe existing data
        // for (size_t i = 0; i < size_; ++i) {
        //     data_[i].~T();
        // }

        // ::operator delete(data_);

        // // 2. Copy new data
        // data_ = static_cast<T*>(other.capacity_ * sizeof(T));
        // size_ = 0;
        // capacity_ = other.capacity_;

        // size_t i = 0;
        // try {
        //     for (; i < other.size_; ++i) {
        //         new (data_ + i) T(other.data_[i]);
        //     }

        //     size_ = other.size_;
        // } catch (...) {
        //     for (int j = 0; j < i; ++j) {
        //         data_[i].~T();
        //     }

        //     ::operator delete(data_);
        // }

        // return *this;
    }

    // Stealing
    Vector(Vector&& other) : data_(other.data_), capacity_(other.capacity_), size_(other.size_) noexcept {
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }

    Vector& operator=(Vector&& other) noexcept {
        // 1. Wipe existing data
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }

        ::operator delete(data_);

        // 2. Steal data
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;

        // 3. other: back to default
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;

        return *this;
    }

    T& operator[](size_t index) {
        return data_[index];
    }

    T& at(size_t index) {
        if (index >= size_) throw std::out_of_range("index out of range");
        return data_[index];
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) resize();

        new (data_ + size_) T(value);
        ++size_;
    }

    void push_back(const T&& value) {
        if (size_ >= capacity_) resize();

        new (data_ + size_) T(std::move(value));
        ++size_;
    }

    void pop_back() {
        data_[size_ - 1].~T();
        --size_;
    }

    ~Vector() {
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }

        ::operator delete(data_);
    }

private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void resize() {
        size_t new_capacity = (capacity_ == 0) ? 2 : capacity_ * 2;
        T* new_data = static_cast<T*>(::operator new(new_capacity * sizeof(T)));

        size_t i = 0;
        try {
            for (; i < size_; ++i) {
                new (new_data + i) T(std::move_if_noexcept(data_[i]));
            }
        } catch (...) {
            for (size_t j = 0; j < i; ++j) {
                new_data[j].~T();
            }

            ::operator delete(new_data);
            throw;
        }

        // Delete existing data_
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }
        ::operator delete(data_);

        data_ = new_data;
        capacity_ = new_capacity;
    }
};

int main() {
    Vector<char>* v = new Vector(0, 'a');
    auto v1 = new Vector<char>();

    vector<int> vec(10);
    cout << vec.size() << '\n';
    cout << vec[0] << ", " << vec[5] << '\n';

    vector<char> vec1(10);
    cout << vec1.size() << '\n';
    cout << vec1[0] << ", " << vec1[5] << '\n';
}
