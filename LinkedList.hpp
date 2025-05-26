#pragma once
#include <stdexcept>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* head;
    size_t size;

public:
    LinkedList() : head(nullptr), size(0) {}
    ~LinkedList() {
        Node* cur = head;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
    }

    void Append(T item) {
        Node* new_node = new Node(item);
        if (!head) head = new_node;
        else {
            Node* cur = head;
            while (cur->next) cur = cur->next;
            cur->next = new_node;
        }
        ++size;
    }

    void InsertAt(T item, size_t index) {
        if (index > size) throw std::out_of_range("Index out of range");
        Node* new_node = new Node(item);
        if (index == 0) {
            new_node->next = head;
            head = new_node;
        }
        else {
            Node* cur = head;
            for (size_t i = 0; i < index - 1; ++i) cur = cur->next;
            new_node->next = cur->next;
            cur->next = new_node;
        }
        ++size;
    }

    void RemoveAt(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        else {
            Node* cur = head;
            for (size_t i = 0; i < index - 1; ++i) cur = cur->next;
            Node* temp = cur->next;
            cur->next = temp->next;
            delete temp;
        }
        --size;
    }

    T& Get(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        Node* cur = head;
        for (size_t i = 0; i < index; ++i) cur = cur->next;
        return cur->data;
    }

    size_t GetSize() const { return size; }
};