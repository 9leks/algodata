#include "trees/bst.hpp"

#include "testing.hpp"

void BST_Test() {
    Assert it("BST tests");
    BST<int> bst;

    it.beforeEach = [&]() { bst = {}; };
}
