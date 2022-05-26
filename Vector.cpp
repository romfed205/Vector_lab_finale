#include "Vector.h"

Vector::Vector(const Value* rawArray, const size_t size, float coef)
        : _size(size), _multiplicativeCoef(coef) {
    if (coef < 1) {
        _multiplicativeCoef = 2.0f;
    }
    _capacity = static_cast<int>(static_cast<float>(_size) * _multiplicativeCoef);
    _data = new Value[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = rawArray[i];
    }
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }
    delete[] _data;
    _data = new Value[other._capacity];
    for (int i = 0; i < other._size; ++i) {
        _data[i] = std::move(other._data[i]);
    }
    _size = other._size;
    _capacity = other._capacity;
    return *this;
}

Vector::Vector(Vector&& other) noexcept {
    *this = std::move(other);
}

Vector& Vector::operator=(Vector&& other) noexcept
{
    if (this == &other) {
        return *this;
    }
    std::swap(_data, other._data);
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
    std::swap(_multiplicativeCoef, other._multiplicativeCoef);
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
    other._multiplicativeCoef = 0;
    return *this;
}

Vector::~Vector() {
    delete[] _data;
}

void Vector::pushBack(const Value& value) {
    insert(value, _size);
}

void Vector::pushFront(const Value& value) {
    insert(value, 0);
}

void Vector::insert(const Value& value, size_t pos) {
    Value arr[]{value};
    insert(arr, 1, pos);
}

void Vector::insert(const Value* values, size_t size, size_t pos)
{
    if (pos > _size) {
        return;
    }
    _size += size;
    if (_capacity <= _size) {
        _capacity += size;
        _capacity *= _multiplicativeCoef;
        insertReAllocCopyToPos(_size - size - 1, pos, size);
    }
    else {
        for (int i = _size - size - 1; i >= pos && i != -1; --i) {
            _data[i + size] = std::move(_data[i]);
        }
    }
    for (int i = pos; i < pos + size; ++i) {
        _data[i] = values[i - pos];
    }
}

void Vector::insert(const Vector& vector, size_t pos) {
    insert(vector._data, vector._size, pos);
}

void Vector::popBack() {
    isEmpty();
    --_size;
}

void Vector::popFront() {
    isEmpty();
    --_size;
    Value* newData = new Value[_capacity];
    for (int i = 0; i < _size; ++i) {
        newData[i] = _data[i + 1];
    }
    delete[] _data;
    _data = newData;
}

void Vector::erase(size_t pos, size_t count) {
    isEmpty();
    size_t end = pos + count;
    if (end > _size) {
        end = _size;
    }
    size_t k = 0;
    for (size_t i = end; i < _size; ++i) {
        _data[pos + k] = _data[i];
        ++k;
    }
    _size -= end - pos;
}

void Vector::eraseBetween(size_t beginPos, size_t endPos) {
    if (beginPos >= endPos || endPos > _size) {
        return;
    }
    erase(beginPos, endPos - beginPos);
}
Value& Vector::operator[](size_t idx) {
    return _data[idx];
}

const Value& Vector::operator[](size_t idx) const {
    return _data[idx];
}

size_t Vector::size() const {
    return _size;
}

size_t Vector::capacity() const {
    return _capacity;
}

double Vector::loadFactor() const {
    return double(_size) / double(_capacity);
}

long long Vector::find(const Value& value) const {
    for (int i = 0; i < _size; ++i) {
        if (_data[i] == value) {
            return i;
        }
    }
    return -1;
}

void Vector::reserve(size_t capacity) {
    if (capacity <= _capacity) {
        return;
    }
    _capacity = capacity;
    Value* newData = new Value[_capacity];
    for (int i = 0; i < _size; ++i) {
        newData[i] = std::move(_data[i]);
    }
    delete[] _data;
    _data = newData;
}

void Vector::shrinkToFit() {
    if (_size == _capacity) {
        return;
    }
    _capacity = _size;
    Value* newData = new Value[_capacity];
    for (int i = 0; i < _size; ++i) {
        newData[i] = std::move(_data[i]);
    }
    delete[] _data;
    _data = newData;
}


//incorrect(solved)
void Vector::insertReAllocCopyToPos(int from, int pos, int shift)
{
    Value* newData = new Value[_capacity];
    for (int i = from; i >= pos && i != -1; --i) {
        newData[i + shift] = std::move(_data[i]);
    }
    for (int i = 0; i < pos; ++i) {
        newData[i] = std::move(_data[i]);
    }
    delete[] _data;
    _data = newData;
}

void Vector::isEmpty() {
    if (_size == 0) {
        throw std::out_of_range("Empty vector popBack");
    }
}
