#pragma once

#include <iostream>
#include <utility>

namespace MyTrees
{
    template <typename T>
    class MyBST
    {
    private:
        struct Node
        {
            T data;
            Node *left;
            Node *right;

            explicit Node(const T &value)
                : data(value), left(nullptr), right(nullptr)
            {
            }
        };

    public:
        MyBST() noexcept
            : root(nullptr), size_(0)
        {
        }

        MyBST(const MyBST &other)
            : root(clone(other.root)), size_(other.size_)
        {
        }

        MyBST(MyBST &&other) noexcept
            : root(other.root), size_(other.size_)
        {
            other.root = nullptr;
            other.size_ = 0;
        }

        MyBST &operator=(MyBST other) noexcept
        {
            swap(other);
            return *this;
        }

        ~MyBST()
        {
            clear(root);
            root = nullptr;
            size_ = 0;
        }

        void swap(MyBST &other) noexcept
        {
            std::swap(root, other.root);
            std::swap(size_, other.size_);
        }

        Node *find(const T &value) const
        {
            return sfind(root, value);
        }

        bool insert(const T &value)
        {
            size_t oldSize = size_;
            sinsert(root, value);
            return size_ > oldSize;
        }

        bool remove(const T &value)
        {
            size_t oldSize = size_;
            sremove(root, value);
            return size_ < oldSize;
        }

        void printInOrder() const
        {
            sprintInOrder(root);
            std::cout << std::endl;
        }

        size_t getHeight() const
        {
            return sgetHeight(root);
        }

        bool empty() const noexcept
        {
            return root == nullptr;
        }

        size_t size() const noexcept
        {
            return size_;
        }

    private:
        Node *root;
        size_t size_;

        static Node *clone(const Node *node)
        {
            if (node == nullptr)
            {
                return nullptr;
            }
            Node *copy = new Node(node->data);
            copy->left = clone(node->left);
            copy->right = clone(node->right);
            return copy;
        }

        static void clear(Node *node)
        {
            if (node == nullptr)
            {
                return;
            }
            clear(node->left);
            clear(node->right);
            delete node;
        }

        static Node *sfind(Node *node, const T &value)
        {
            if (nullptr == node)
            {
                return nullptr;
            }

            if (value == node->data)
            {
                return node;
            }
            else if (value < node->data)
            {
                return sfind(node->left, value);
            }
            else
            {
                return sfind(node->right, value);
            }
        }

        void sinsert(Node *&node, const T &value)
        {
            if (nullptr == node)
            {
                node = new Node(value);
                ++size_;
                return;
            }

            if (value < node->data)
            {
                sinsert(node->left, value);
            }
            else if (value > node->data)
            {
                sinsert(node->right, value);
            }
        }

        void sremove(Node *&node, const T &value)
        {
            if (node == nullptr)
            {
                return;
            }

            if (value < node->data)
            {
                sremove(node->left, value);
            }
            else if (value > node->data)
            {
                sremove(node->right, value);
            }
            else
            {
                // A leaf node - without children
                if (nullptr == node->left && nullptr == node->right)
                {
                    delete node;
                    node = nullptr;
                    --size_;
                }
                // A node with only right child
                else if (nullptr == node->left)
                {
                    Node *temp = node->right;
                    delete node;
                    node = temp;
                    --size_;
                }
                // A node with only left child
                else if (nullptr == node->right)
                {
                    Node *temp = node->left;
                    delete node;
                    node = temp;
                    --size_;
                }
                // Node with two children
                else
                {
                    Node *successor = findMin(node->right);
                    node->data = successor->data;
                    sremove(node->right, successor->data);
                }
            }
        }

        static Node *findMin(Node *node)
        {
            if (nullptr == node)
            {
                return nullptr;
            }
            while (nullptr == node->left)
            {
                node = node->left;
            }
            return node;
        }

        static void sprintInOrder(Node *node)
        {
            if (node == nullptr)
            {
                return;
            }
            sprintInOrder(node->left);
            std::cout << node->data << " ";
            sprintInOrder(node->right);
        }

        static size_t sgetHeight(Node *node)
        {
            if (nullptr == node)
            {
                return 0;
            }
            size_t leftHeight = sgetHeight(node->left);
            size_t rightHeight = sgetHeight(node->right);
            return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
        }
    };
} // namespace MyTrees
