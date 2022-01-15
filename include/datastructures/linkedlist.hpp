#pragma once

#include <fmt/core.h>

#include <initializer_list>
#include <list>
#include <stdexcept>
#include <utility>

#include "node.hpp"
#include "stack.hpp"

template <typename T>
struct LinkedList {
    Node<T>* head{nullptr};
    std::size_t size{0};

    LinkedList() = default;

    LinkedList(const LinkedList& other) {
        Stack<T> stack;

        for (auto curr{other.head}; curr != nullptr; curr = curr->next) {
            stack.push(curr->val);
        }

        while (!stack.is_empty()) {
            prepend(stack.pop());
        }
    }

    LinkedList(LinkedList&& other) {
        swap(*this, other);
    }

    LinkedList(std::initializer_list<T> vals) {
        for (auto val{std::rbegin(vals)}; val != std::rend(vals); val++) {
            prepend(*val);
        }
    }

    ~LinkedList() {
        while (head != nullptr) {
            delete std::exchange(head, head->next);
        }
    }

    friend void swap(LinkedList<T>& lhs, LinkedList<T>& rhs) {
        std::swap(lhs.size, rhs.size);
        std::swap(lhs.head, rhs.head);
    }

    LinkedList<T>& operator=(LinkedList<T> other) {
        using std::swap;
        swap(*this, other);
        return *this;
    }

    bool operator==(const LinkedList<T> other) const {
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

    void prepend(T const& val) {
        head = new Node<T>(val, head);
        size++;
    }

    void append(T const& val) {
        if (is_empty()) {
            head = new Node<T>(val);
            return;
        }

        auto tail{head};
        while (tail->next != nullptr) {
            tail = tail->next;
        }
        tail->next = new Node<T>(val);
        size++;
    }

    void insert(T const& val, unsigned int idx) {
        if (idx == 0) {
            prepend(val);
            return;
        } else if (idx == size) {
            append(val);
            return;
        }

        auto elem{head};
        for (unsigned int i{0}; i < idx - 1; i++) {
            elem = elem->next;
        }
        auto next{elem->next};
        elem->next = new Node(val, next);
        size++;
    }

    T get(unsigned int idx) const {
        if (is_empty() || idx >= size) {
            auto msg{fmt::format("out-of-bounds index {} for LinkedList::get(unsigned int)\n", idx)};
            throw std::runtime_error(msg);
        }

        auto elem{head};
        for (unsigned int i{0}; i < idx; i++) {
            elem = elem->next;
        }
        return elem->val;
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
