#ifndef JSON_HPP
#define JSON_HPP

#include <iostream>
#include <stack>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::stack;

namespace json {
    struct Node {
            Node() = default;
            ~Node() = default;

            // TODO: change to dynamic memmory and classes
            string _key;
            string _value;
            vector<const Node*> _siblings{};
    };


    struct JSONTree {
            JSONTree() = default;
            ~JSONTree() = default;

            void addChild(const Node *child) {
                _root->_siblings.push_back(child);
            }

            Node *_root = nullptr;

    };
} // namespace json
#endif // JSON_HPP
