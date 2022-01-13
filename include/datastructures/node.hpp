#pragma once

template <typename T>
struct Node {
    T val;
    Node<T>* next;

    explicit Node(T const& val) : val{val}, next{nullptr} {}
    Node(T const& val, Node<T>* const& next) : val{val}, next{next} {}
};
