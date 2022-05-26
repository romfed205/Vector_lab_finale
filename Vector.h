#pragma once

#include <cstddef>
#include <utility>
#include <stdexcept>

using Value = double;
class Vector
{
public:
    Vector() = default;

    Vector(const Value* rawArray, const size_t size, float coef = 2.0);

    Vector(const Vector& other)
    : Vector(other._data, other._size, other._multiplicativeCoef) {
    }

    Vector& operator=(const Vector& other);

    Vector(Vector&& other) noexcept;

    Vector& operator=(Vector&& other) noexcept;

    ~Vector();

    void pushBack(const Value& value);

    void pushFront(const Value& value);

    void insert(const Value& value, size_t pos);

    void insert(const Value* values, size_t size, size_t pos);

    void insert(const Vector& vector, size_t pos);

    void popBack();

    void popFront();


    void erase(size_t pos, size_t count);

    void eraseBetween(size_t beginPos, size_t endPos);

    Value& operator[](size_t idx);

    const Value& operator[](size_t idx) const;

    [[nodiscard]] size_t size() const;

    [[nodiscard]] size_t capacity() const;

    [[nodiscard]] double loadFactor() const;

    long long find(const Value& value) const;

    void reserve(size_t capacity);

    void shrinkToFit();

    class Iterator {
    public:
        explicit Iterator(Value* ptr) : _ptr(ptr) {}

        Value & operator*() {
            return *_ptr;
        }

        const Value& operator*() const {
            return *_ptr;
        }

        Value* operator->() {
            return _ptr;
        }

        const Value* operator->() const {
            return _ptr;
        }

        Iterator operator++() {
            ++_ptr;
            return *this;
        }

        Iterator operator++(int) {
            Value* bPtr = _ptr;
            ++_ptr;
            return Iterator(bPtr);
        }

        Iterator operator--() {
            --_ptr;
            return *this;
        }

        Iterator operator--(int) {
            Value* bPtr = _ptr;
            --_ptr;
            return Iterator(bPtr);
        }

        bool operator==(const Iterator& other) const {
            return _ptr == other._ptr;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

    private:
        Value* _ptr;
    };

    Iterator begin() {
        return Iterator(&(_data[0]));
    }

    Iterator end() {
        return Iterator(&_data[_size]);
    }

private:
    Value* _data{nullptr};
    size_t _size{};
    size_t _capacity{};
    float _multiplicativeCoef{2.0f};

    void insertReAllocCopyToPos(int from, int pos, int shift);

    void isEmpty();
};
