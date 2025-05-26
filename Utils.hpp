#pragma once
#include <functional>
#include "Sequence.hpp"
#include "ArraySequence.hpp"

template<class T, typename Mapper> 
Sequence<T>* map(Sequence<T>* seq, Mapper mapper) {
    ArraySequence<T>* result = new ArraySequence<T>();
    for (size_t i = 0; i < seq->GetSize(); ++i) {
        result->Append(mapper(seq->Get(i))); 
    }
    return result;
}

template<class T, typename Predicate>
Sequence<T>* where(Sequence<T>* seq, Predicate pred) {  
    ArraySequence<T>* result = new ArraySequence<T>();
    for (size_t i = 0; i < seq->GetSize(); ++i) {
        T item = seq->Get(i);
        if (pred(item)) { 
            result->Append(item);
        }
    }
    return result;
}

template<class T, typename Reducer>
T reduce(Sequence<T>* seq, Reducer reducer, T initial) {
    T result = initial;
    for (size_t i = 0; i < seq->GetSize(); ++i) {
        result = reducer(result, seq->Get(i));
    }
    return result;
}
