#include <cassert>
#include <iostream>
#include <string>
#include "MyStackArrayImpl.hpp"

namespace MyStackArrayImpl
{
    int MyStackArrayImplUTests()
    {
        // Tests for int type
        {
            MyStackArrayImpl<int> stack;
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
        }

        // Tests for char type
        {
            MyStackArrayImpl<char> charStack;
            assert(charStack.isEmpty());

            charStack.push('a');
            charStack.push('b');
            charStack.push('c');
            assert(charStack.tos == 3);
            assert(charStack.peek() == 'c');

            char c = charStack.pop();
            assert(c == 'c');
            c = charStack.pop();
            assert(c == 'b');
            assert(charStack.peek() == 'a');

            charStack.pop();
            assert(charStack.isEmpty());
        }

        // Tests for std::string type
        {
            MyStackArrayImpl<std::string> stringStack;
            assert(stringStack.isEmpty());

            stringStack.push("hello");
            stringStack.push("world");
            stringStack.push("cpp");
            assert(stringStack.tos == 3);
            assert(stringStack.peek() == "cpp");

            std::string s = stringStack.pop();
            assert(s == "cpp");
            assert(stringStack.peek() == "world");

            s = stringStack.pop();
            assert(s == "world");
            s = stringStack.pop();
            assert(s == "hello");
            assert(stringStack.isEmpty());
        }

        // Test pop on empty stack throws exception
        {
            MyStackArrayImpl<int> stack;
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
            MyStackArrayImpl<int> stack;
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

        std::cout << "MyStackArrayImpl tests passed (int, char, string).\n";
        return 0;
    }
} // namespace MyStackArrayImpl
