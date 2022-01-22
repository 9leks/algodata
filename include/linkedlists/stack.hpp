#pragma once

#include <fmt/core.h>

#include <initializer_list>
#include <list>
#include <stdexcept>
#include <utility>

#include "node.hpp"

template <typename T>
struct Stack {
    Node<T>* head{nullptr};
    std::size_t size{0};

    Stack() = default;

    Stack(const Stack& other) {
        Stack stack;

        for (auto curr{other.head}; curr != nullptr; curr = curr->next) {
            stack.push(curr->val);
        }

        while (!stack.is_empty()) {
            push(stack.pop());
        }
    }

    Stack(Stack&& other) {
        swap(*this, other);
    }

    Stack(std::initializer_list<T> vals) {
        for (auto val{std::rbegin(vals)}; val != std::rend(vals); val++) {
            push(*val);
        }
    }

    ~Stack() {
        while (head != nullptr) {
            delete std::exchange(head, head->next);
        }
    }

    friend void swap(Stack<T>& lhs, Stack<T>& rhs) {
        std::swap(lhs.size, rhs.size);
        std::swap(lhs.head, rhs.head);
    }

    Stack<T>& operator=(Stack<T> other) {
        using std::swap;
        swap(*this, other);
        return *this;
    }

    bool operator==(const Stack<T> other) const {
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

    void push(T const& val) {
        head = new Node<T>(val, head);
        size++;
    }

    T pop() {
        if (is_empty()) {
            throw std::runtime_error("popping empty stack");
        }

        T val = head->val;
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
