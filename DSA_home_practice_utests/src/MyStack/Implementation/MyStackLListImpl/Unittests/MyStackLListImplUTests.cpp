#include <cassert>
#include <iostream>
#include "MyStackLListImpl.hpp"

namespace MyStackLListImpl
{
    int MyStackLListImplUTests()
    {
        // Test basic push and pop
        {
            MyStackLListImpl stack;
            assert(stack.isEmpty());
            assert(!stack.isFull());
            assert(stack.tos == 0);

            stack.push(10);
            assert(!stack.isEmpty());
            assert(stack.tos == 1);
            assert(stack.peek() == 10);

            stack.push(20);
            stack.push(30);
            assert(stack.tos == 3);
            assert(stack.peek() == 30);

            int val = stack.pop();
            assert(val == 30);
            assert(stack.tos == 2);
            assert(stack.peek() == 20);

            val = stack.pop();
            assert(val == 20);
            val = stack.pop();
            assert(val == 10);
            assert(stack.isEmpty());
            assert(stack.tos == 0);
        }

        // Test multiple pushes and pops
        {
            MyStackLListImpl stack;

            for (int i = 0; i < 10; ++i)
            {
                stack.push(i * 10);
            }
            assert(stack.tos == 10);
            assert(stack.peek() == 90);

            for (int i = 9; i >= 0; --i)
            {
                int val = stack.pop();
                assert(val == i * 10);
            }
            assert(stack.isEmpty());
        }

        // Test pop on empty stack throws exception
        {
            MyStackLListImpl stack;
            try
            {
                stack.pop();
                assert(false); // Should have thrown
            }
            catch (const std::out_of_range &e)
            {
                // Expected
            }
        }

        // Test peek on empty stack throws exception
        {
            MyStackLListImpl stack;
            try
            {
                stack.peek();
                assert(false); // Should have thrown
            }
            catch (const std::out_of_range &e)
            {
                // Expected
            }
        }

        // Test alternating push and pop
        {
            MyStackLListImpl stack;

            stack.push(5);
            assert(stack.peek() == 5);

            stack.push(15);
            assert(stack.peek() == 15);

            int val = stack.pop();
            assert(val == 15);
            assert(stack.peek() == 5);

            stack.push(25);
            assert(stack.peek() == 25);

            val = stack.pop();
            assert(val == 25);
            val = stack.pop();
            assert(val == 5);
            assert(stack.isEmpty());
        }

        // Test isFull always returns false for linked list implementation
        {
            MyStackLListImpl stack;
            assert(!stack.isFull());

            for (int i = 0; i < 100; ++i)
            {
                stack.push(i);
            }
            assert(!stack.isFull()); // Should always be false
            assert(stack.tos == 100);
        }

        std::cout << "MyStackLListImpl tests passed.\n";
        return 0;
    }
} // namespace MyStackLListImpl
