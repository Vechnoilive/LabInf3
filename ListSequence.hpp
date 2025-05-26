#pragma once
#include "Sequence.hpp"
#include "LinkedList.hpp"

template <typename T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T> list;
public:
    T& Get(size_t index) override { return list.Get(index); }
    void Append(T item) override { list.Append(item); }
    void InsertAt(T item, size_t index) override { list.InsertAt(item, index); }
    void RemoveAt(size_t index) override { list.RemoveAt(index); }
    size_t GetSize() const override { return list.GetSize(); }
};