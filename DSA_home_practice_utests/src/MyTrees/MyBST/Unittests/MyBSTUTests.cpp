// MyBST UTests compilation unit

#include <cassert>
#include <iostream>
#include <string>
#include "../Implementation/MyBST.hpp"
#include "MyBSTUTests.hpp"

namespace MyTrees
{
    void MyBSTUTests()
    {
        std::cout << "\n=== MyBST Unit Tests ===" << std::endl;

        // Test 1: Default constructor
        {
            MyBST<int> bst;
            assert(bst.empty());
            assert(bst.size() == 0);
            assert(bst.getHeight() == 0);
            std::cout << "✓ Test 1: Default constructor" << std::endl;
        }

        // Test 2: Single insert
        {
            MyBST<int> bst;
            assert(bst.insert(50));
            assert(bst.size() == 1);
            assert(!bst.empty());
            assert(bst.find(50) != nullptr);
            assert(bst.getHeight() == 1);
            std::cout << "✓ Test 2: Single insert" << std::endl;
        }

        // Test 3: Multiple inserts and BST property
        {
            MyBST<int> bst;
            bst.insert(50);
            bst.insert(30);
            bst.insert(70);
            bst.insert(20);
            bst.insert(40);
            bst.insert(60);
            bst.insert(80);
            assert(bst.size() == 7);
            assert(bst.find(20) != nullptr);
            assert(bst.find(100) == nullptr);
            assert(bst.getHeight() == 3);
            std::cout << "✓ Test 3: Multiple inserts and BST property" << std::endl;
        }

        // Test 4: No duplicate inserts
        {
            MyBST<int> bst;
            assert(bst.insert(50));
            assert(!bst.insert(50)); // Duplicate should not increase size
            assert(bst.size() == 1);
            std::cout << "✓ Test 4: No duplicate inserts" << std::endl;
        }

        // Test 5: In-order traversal
        {
            MyBST<int> bst;
            bst.insert(50);
            bst.insert(30);
            bst.insert(70);
            bst.insert(20);
            bst.insert(40);
            bst.insert(60);
            bst.insert(80);
            std::cout << "  In-order: ";
            bst.printInOrder();
            // Expected: 20 30 40 50 60 70 80
            std::cout << "✓ Test 5: In-order traversal" << std::endl;
        }

        // Test 6: Remove leaf node
        {
            MyBST<int> bst;
            bst.insert(50);
            bst.insert(30);
            bst.insert(70);
            bst.insert(20);
            assert(bst.remove(20));
            assert(bst.find(20) == nullptr);
            assert(bst.size() == 3);
            std::cout << "✓ Test 6: Remove leaf node" << std::endl;
        }

        // Test 7: Remove node with one child
        {
            MyBST<int> bst;
            bst.insert(50);
            bst.insert(30);
            bst.insert(70);
            bst.insert(20);
            assert(bst.remove(30));
            assert(bst.find(30) == nullptr);
            assert(bst.find(20) != nullptr);
            assert(bst.size() == 3);
            std::cout << "✓ Test 7: Remove node with one child" << std::endl;
        }

        // Test 8: Remove node with two children
        {
            MyBST<int> bst;
            bst.insert(50);
            bst.insert(30);
            bst.insert(70);
            bst.insert(20);
            bst.insert(40);
            bst.insert(60);
            bst.insert(80);
            assert(bst.remove(50)); // Root with two children
            assert(bst.find(50) == nullptr);
            assert(bst.size() == 6);
            assert(bst.find(20) != nullptr);
            assert(bst.find(40) != nullptr);
            assert(bst.find(70) != nullptr);
            std::cout << "✓ Test 8: Remove node with two children" << std::endl;
        }

        // Test 9: Remove non-existent node
        {
            MyBST<int> bst;
            bst.insert(50);
            assert(!bst.remove(100));
            assert(bst.size() == 1);
            std::cout << "✓ Test 9: Remove non-existent node" << std::endl;
        }

        // Test 10: Copy constructor
        {
            MyBST<int> bst1;
            bst1.insert(50);
            bst1.insert(30);
            bst1.insert(70);

            MyBST<int> bst2(bst1);
            assert(bst2.size() == 3);
            assert(bst2.find(50) != nullptr);
            assert(bst2.find(30) != nullptr);
            assert(bst2.find(70) != nullptr);

            // Modify bst1 and ensure bst2 is unaffected
            bst1.insert(100);
            assert(bst1.size() == 4);
            assert(bst2.size() == 3);
            assert(bst2.find(100) == nullptr);
            std::cout << "✓ Test 10: Copy constructor" << std::endl;
        }

        // Test 11: Copy assignment
        {
            MyBST<int> bst1;
            bst1.insert(50);
            bst1.insert(30);

            MyBST<int> bst2;
            bst2.insert(100);

            bst2 = bst1;
            assert(bst2.size() == 2);
            assert(bst2.find(50) != nullptr);
            assert(bst2.find(30) != nullptr);
            assert(bst2.find(100) == nullptr);

            // Modify bst1 and ensure bst2 is unaffected
            bst1.insert(200);
            assert(bst1.size() == 3);
            assert(bst2.size() == 2);
            std::cout << "✓ Test 11: Copy assignment" << std::endl;
        }

        // Test 12: Move constructor
        {
            MyBST<int> bst1;
            bst1.insert(50);
            bst1.insert(30);
            bst1.insert(70);

            MyBST<int> bst2(std::move(bst1));
            assert(bst2.size() == 3);
            assert(bst2.find(50) != nullptr);
            assert(bst1.empty()); // bst1 should be empty after move
            std::cout << "✓ Test 12: Move constructor" << std::endl;
        }

        // Test 13: Move assignment
        {
            MyBST<int> bst1;
            bst1.insert(50);
            bst1.insert(30);

            MyBST<int> bst2;
            bst2 = std::move(bst1);
            assert(bst2.size() == 2);
            assert(bst2.find(50) != nullptr);
            assert(bst1.empty()); // bst1 should be empty after move
            std::cout << "✓ Test 13: Move assignment" << std::endl;
        }

        // Test 14: String BST
        {
            MyBST<std::string> bst;
            bst.insert("dog");
            bst.insert("cat");
            bst.insert("elephant");
            bst.insert("ant");
            assert(bst.size() == 4);
            assert(bst.find("dog") != nullptr);
            assert(bst.find("cat") != nullptr);
            assert(bst.find("elephant") != nullptr);
            assert(bst.find("ant") != nullptr);
            assert(bst.find("zebra") == nullptr);
            std::cout << "✓ Test 14: String BST" << std::endl;
        }

        // Test 15: Height calculation
        {
            MyBST<int> bst;
            assert(bst.getHeight() == 0); // Empty tree
            bst.insert(50);
            assert(bst.getHeight() == 1);
            bst.insert(30);
            assert(bst.getHeight() == 2);
            bst.insert(70);
            assert(bst.getHeight() == 2);
            bst.insert(20);
            assert(bst.getHeight() == 3);
            std::cout << "✓ Test 15: Height calculation" << std::endl;
        }

        // Test 16: Destructor and memory cleanup
        {
            {
                MyBST<int> bst;
                for (int i = 0; i < 100; ++i)
                {
                    bst.insert(i);
                }
                assert(bst.size() == 100);
            } // Destructor called here
            std::cout << "✓ Test 16: Destructor and memory cleanup" << std::endl;
        }

        std::cout << "=== All MyBST Unit Tests Passed ===" << std::endl;
    }
} // namespace MyTrees

