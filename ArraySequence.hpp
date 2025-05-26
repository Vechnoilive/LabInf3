#pragma once
#include "Sequence.hpp"
#include "DynamicArray.hpp"

template <typename T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T> array;
public:
    T& Get(size_t index) override { return array[index]; }
    void Append(T item) override { array.Append(item); }
    void InsertAt(T item, size_t index) override { array.InsertAt(item, index); }
    void RemoveAt(size_t index) override { array.RemoveAt(index); }
    size_t GetSize() const override { return array.GetSize(); }
};