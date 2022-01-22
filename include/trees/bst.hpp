#pragma once

#include <fmt/core.h>

#include <initializer_list>
#include <list>
#include <stdexcept>
#include <utility>

#include "tree.hpp"

template <typename T>
struct BST {
    Tree<T>* root{nullptr};
    std::size_t size{0};

    BST() = default;

    BST(const BST& other) {
        // ...
    }

    BST(BST&& other) : BST{} {
        swap(*this, other);
    }

    BST(std::initializer_list<T> vals) : BST{} {
        for (auto val : vals) {
            insert(val);
        }
    }

    ~BST() {
        delete root;
    }

    friend void swap(BST<T>& lhs, BST<T>& rhs) {
        std::swap(lhs.root, rhs.root);
        std::swap(lhs.size, rhs.size);
    }

    BST<T>& operator=(BST<T> other) {
        using std::swap;
        swap(*this, other);
        return *this;
    }

    bool find(const T& val) {
        auto next = root;
        decltype(next) node = nullptr;

        while (next != nullptr) {
            node = next;
            if (val < next.val) {
                next = node.left;
            } else if (val > next.val) {
                next = next.right;
            } else {
                throw std::runtime_error("duplicate value error");
            }
        }

        return node != nullptr && node.val == val;
    }

    void insert(const T& val) {
        auto next = root;
        decltype(next) node = nullptr;

        while (next != nullptr) {
            node = next;
            if (val < next.val) {
                next = node.left;
            } else if (val > next.val) {
                next = next.right;
            } else {
                throw std::runtime_error("duplicate value error");
            }
        }

        // if ()
    }

    void remove(const T& val);
    void inorder(Tree<T> node);
    void preorder(Tree<T> node);
    void postorder(Tree<T> node);
};
