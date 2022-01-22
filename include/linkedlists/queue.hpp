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
    Node<T>* head{nullptr};
    Node<T>* tail{nullptr};
    std::size_t size{0};

    Queue() = default;

    Queue(const Queue& other) {
        for (auto curr{other.head}; curr != nullptr; curr = curr->next) {
            enqueue(curr->val);
        }
    }

    Queue(Queue&& other) {
        swap(*this, other);
    }

    Queue(std::initializer_list<T> vals) {
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
        std::swap(lhs.size, rhs.size);
        std::swap(lhs.head, rhs.head);
        std::swap(lhs.tail, rhs.tail);
    }

    Queue<T>& operator=(Queue<T> other) {
        using std::swap;
        swap(*this, other);
        return *this;
    }

    bool operator==(const Queue<T> other) const {
        if (size != other.size) {
            return false;
        }

        auto curr1{head};
        auto curr2{other.head};

        for (unsigned int i{0}; i < size; i++) {
            if (curr1->val != curr2->val) {
                return false;
            }
            curr1 = curr1->next;
            curr2 = curr2->next;
        }

        return true;
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
