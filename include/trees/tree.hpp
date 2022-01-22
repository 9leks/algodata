#include <utility>

template <typename T>
struct Tree {
    T val;
    Tree<T>* left{nullptr};
    Tree<T>* right{nullptr};

    Tree(T const& val) : val{val} {}
    Tree(T const& val, Tree<T>* const& left, Tree<T>* const& right) : val{val}, left{left}, right{right} {}

    Tree(const Tree& other) {
        left = copy(other.left);
        right = copy(other.right);
    }

    Tree(Tree&& other) : Tree{} {
        swap(*this, other);
    }

    ~Tree() {
        delete left;
        delete right;
    }

    friend void swap(Tree<T>& lhs, Tree<T>& rhs) {
        std::swap(lhs.root, rhs.root);
        std::swap(lhs.size, rhs.size);
    }

    Tree<T>& operator=(Tree<T> other) {
        using std::swap;
        swap(*this, other);
        return *this;
    }

   private:
    Tree<T>& copy(Tree<T> root) {
        if (!root) {
            return nullptr;
        }

        auto tree{new Tree<T>(root->val)};
        tree.left = copy(root.left);
        tree.right = copy(root.right);
        return tree;
    }
};
