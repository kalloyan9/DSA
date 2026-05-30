#include <cassert>
#include <iostream>
#include <utility>
#include "MyGenericTree.hpp"

namespace MyTrees
{
    int MyGenericTreeUTests()
    {
        Tree<int> tree;
        Node<int> *root = tree.insertAsSibling(1, nullptr);
        assert(root != nullptr);
        assert(tree.getSize() == 1);

        Node<int> *childA = tree.insertAsSibling(2, root);
        Node<int> *childB = tree.insertAsSibling(3, root);
        assert(tree.getSize() == 3);
        assert(tree.findElementDFS(2) == childA);
        assert(tree.findElementBFS(3) == childB);

        Tree<int> copy = tree;
        assert(copy.getSize() == tree.getSize());
        assert(copy.getRoot()->data == 1);
        assert(copy.findElementDFS(2)->data == 2);

        Tree<int> moved = std::move(copy);
        assert(moved.getSize() == 3);
        assert(copy.getSize() == 0);

        std::cout << "MyGenericTree tests passed.\n";
        return 0;
    }
} // namespace MyTrees
