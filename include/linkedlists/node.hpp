#pragma once

template <typename T>
struct Node {
    T val;
    Node<T>* next{nullptr};

    Node(T const& val) : val{val} {}
    Node(T const& val, Node<T>* const& next) : val{val}, next{next} {}
};
