#pragma once
#include <stdexcept>

template <typename T>
class DynamicArray {
private:
    T* data;
    size_t size;
    size_t capacity;

    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size; ++i) new_data[i] = data[i];
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    DynamicArray() : data(new T[1]), size(0), capacity(1) {}
    ~DynamicArray() { delete[] data; }

    void Append(T item) {
        if (size == capacity) resize(capacity * 2);
        data[size++] = item;
    }

    void InsertAt(T item, size_t index) {
        if (index > size) throw std::out_of_range("Index out of range");
        if (size == capacity) resize(capacity * 2);
        for (size_t i = size; i > index; --i) data[i] = data[i - 1];
        data[index] = item;
        ++size;
    }

    void RemoveAt(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        for (size_t i = index; i < size - 1; ++i) data[i] = data[i + 1];
        --size;
    }

    T& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    size_t GetSize() const { return size; }
};