#pragma once
#include <iostream>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

namespace MyTrees
{
    template <typename T>
    struct Node
    {
        T data;
        std::vector<Node*> children;

        explicit Node(const T &value)
            : data(value), children()
        {
        }
    };

    template <typename T>
    class Tree
    {
    public:
        // big five
        Tree() noexcept
            : root(nullptr), size_(0)
        {
        }

        Tree(const Tree &other)
            : root(clone(other.root)), size_(other.size_)
        {
        }

        Tree(Tree &&other) noexcept
            : root(other.root), size_(other.size_)
        {
            other.root = nullptr;
            other.size_ = 0;
        }

        Tree &operator=(Tree other) noexcept
        {
            swap(other);
            return *this;
        }

        ~Tree()
        {
            clear(root);
            root = nullptr;
            size_ = 0;
        }

        void swap(Tree &other) noexcept
        {
            std::swap(root, other.root);
            std::swap(size_, other.size_);
        }

        Node<T> *getRoot() const noexcept
        {
            return root;
        }

        size_t getSize() const noexcept
        {
            return size_;
        }

        Node<T> *insertAsSibling(const T &element, Node<T> *parent)
        {
            if (parent == nullptr)
            {
                if (root != nullptr)
                {
                    throw std::invalid_argument("Parent cannot be null when tree already has a root.");
                }
                root = new Node<T>(element);
                size_ = 1;
                return root;
            }

            Node<T> *child = new Node<T>(element);
            parent->children.push_back(child);
            ++size_;
            return child;
        }

        void printTreeDFS() const
        {
            std::cout << "Total elements: " << size_ << std::endl;
            sprintTreeDFS(root);
        }

        void printTreeBFS() const
        {
            std::cout << "Total elements: " << size_ << std::endl;
            sprintTreeBFS(root);
        }

        Node<T> *findElementDFS(const T &element) const
        {
            return sfindElementDFS(root, element);
        }

        Node<T> *findElementBFS(const T &element) const
        {
            return sfindElementBFS(root, element);
        }

    // static utility functions
    private:
        static Node<T> *clone(const Node<T> *node)
        {
            if (nullptr == node)
            {
                return nullptr;
            }

            Node<T> *copy = new Node<T>(node->data);
            for (const Node<T> *child : node->children)
            {
                copy->children.push_back(clone(child));
            }
            return copy;
        }

        static void clear(Node<T> *node)
        {
            if (nullptr == node)
            {
                return;
            }

            for (Node<T> *child : node->children)
            {
                clear(child);
            }
            delete node;
        }

        static void sprintTreeDFS(Node<T> *node)
        {
            if (nullptr == node)
            {
                return;
            }

            std::cout << "Node: " << node->data << std::endl;
            for (Node<T> *child : node->children)
            {
                sprintTreeDFS(child);
            }
        }

        static Node<T> *sfindElementDFS(Node<T> *node, const T &element)
        {
            if (nullptr == node)
            {
                return nullptr;
            }
            if (element == node->data)
            {
                return node;
            }

            for (Node<T> *child : node->children)
            {
                Node<T> *found = sfindElementDFS(child, element);
                if (nullptr != found)
                {
                    return found;
                }
            }
            return nullptr;
        }

        static Node<T> *sfindElementBFS(Node<T> *node, const T &element)
        {
            if (nullptr == node)
            {
                return nullptr;
            }

            std::queue<Node<T> *> q;
            q.push(node);
            while (!q.empty())
            {
                Node<T> *current = q.front();
                q.pop();
                if (element == current->data)
                {
                    return current;
                }
                for (Node<T> *child : current->children)
                {
                    q.push(child);
                }
            }
            return nullptr;
        }

    // data members
    private:
        Node<T> *root;
        size_t size_;
    };

} // namespace MyTrees
