#pragma once

template <typename T>
class Sequence {
public:
    virtual T& Get(size_t index) = 0;
    virtual void Append(T item) = 0;
    virtual void InsertAt(T item, size_t index) = 0;
    virtual void RemoveAt(size_t index) = 0;
    virtual size_t GetSize() const = 0;
    virtual ~Sequence() {}
};