#pragma once

#include <fmt/core.h>

#include <initializer_list>
#include <list>
#include <stdexcept>
#include <utility>

#include "node.hpp"
#include "stack.hpp"

template <typename T>
struct Queue {
    Node<T>* head;
    Node<T>* tail;
    std::size_t size;

    Queue() : head{nullptr}, tail{nullptr}, size{0} {}

    Queue(const Queue& other) {
        for (auto curr{other.head}; curr != nullptr; curr = curr->next) {
            enqueue(curr->val);
        }
    }

    Queue(Queue&& other) : Queue{} {
        swap(*this, other);
    }

    Queue(std::initializer_list<T> vals) : Queue{} {
        for (auto val : vals) {
            enqueue(val);
        }
    }

    ~Queue() {
        while (head != nullptr) {
            delete std::exchange(head, head->next);
        }
    }

    friend void swap(Queue<T>& lhs, Queue<T>& rhs) {
        using std::swap;
        swap(lhs.size, rhs.size);
        swap(lhs.head, rhs.head);
        swap(lhs.tail, rhs.tail);
    }

    Queue<T>& operator=(Queue<T> other) {
        using std::swap;
        swap(*this, other);
        return *this;
    }

    void enqueue(T const& val) {
        auto elem{new Node<T>(val)};

        if (is_empty()) {
            head = tail = elem;
        } else {
            tail->next = elem;
            tail = elem;
        }

        size++;
    }

    T dequeue() {
        if (is_empty()) {
            throw std::runtime_error("popping empty queue");
        }

        T val{head->val};
        delete std::exchange(head, head->next);
        size--;
        return val;
    }

    bool is_empty() const {
        return size == 0;
    }

    std::list<T> to_std_list() const {
        std::list<T> list;

        auto curr{head};
        while (curr != nullptr) {
            list.emplace_back(curr->val);
            curr = curr->next;
        }

        return list;
    }
};
