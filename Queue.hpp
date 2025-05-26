#pragma once
#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include <memory>
#include <functional>

template <typename T>
class Queue {
private:
    std::unique_ptr<Sequence<T>> data;
public:
    Queue(Sequence<T>* seq) : data(seq) {}

    void Enqueue(T item) { data->Append(item); }
    T Dequeue() {
        if (data->GetSize() == 0) throw std::out_of_range("Queue is empty");
        T front = data->Get(0);
        data->RemoveAt(0);
        return front;
    }
    T& Front() { return data->Get(0); }
    size_t Size() const { return data->GetSize(); }
    bool IsEmpty() const { return Size() == 0; }
    Sequence<T>* GetSequence() const { return data.get(); }

    Queue<T> Concat(const Queue<T>& other) const {
        Sequence<T>* result = new ArraySequence<T>();
        for (size_t i = 0; i < data->GetSize(); ++i) result->Append(data->Get(i));
        for (size_t i = 0; i < other.Size(); ++i) result->Append(other.data->Get(i));
        return Queue<T>(result);
    }

    Queue<T> SubQueue(size_t start, size_t end) const {
        if (start > end || end > data->GetSize()) throw std::out_of_range("Invalid range");
        Sequence<T>* result = new ArraySequence<T>();
        for (size_t i = start; i < end; ++i) result->Append(data->Get(i));
        return Queue<T>(result);
    }

    bool ContainsSubQueue(const Queue<T>& sub) const {
        if (sub.Size() > this->Size()) return false;
        for (size_t i = 0; i <= this->Size() - sub.Size(); ++i) {
            bool match = true;
            for (size_t j = 0; j < sub.Size(); ++j) {
                if (!(this->data->Get(i + j) == sub.data->Get(j))) {
                    match = false;
                    break;
                }
            }
            if (match) return true;
        }
        return false;
    }

    std::pair<Queue<T>, Queue<T>> Split(std::function<bool(const T&)> pred) const {
        Sequence<T>* first = new ArraySequence<T>();
        Sequence<T>* second = new ArraySequence<T>();
        for (size_t i = 0; i < data->GetSize(); ++i) {
            T item = data->Get(i);
            if (pred(item)) first->Append(item);
            else second->Append(item);
        }
        return { Queue<T>(first), Queue<T>(second) };
    }
};
