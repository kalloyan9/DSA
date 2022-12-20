#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
struct Node{
    T data;
    Node *left = nullptr, *right = nullptr;

    Node(T val, Node *l, Node *r) {
        this->data = val;
        left = l;
        right = r;
    }
};

template <typename T>
void dfs_print(const Node<T> *root, size_t k) {
    if (root == nullptr) {
        return;
    }

    cout << "k: " << k << ": " << root->data << endl;
    dfs_print(root->left, k + 1);
    dfs_print(root->right, k + 1);
}

template <typename T>
void dfs_find_min_el(const Node<T> *root, size_t k, T& min, size_t& min_k) {
    if (root == nullptr) {
        return;
    }

    if (root->data < min) {
        min = root->data;
        min_k = k;
    }

    dfs_find_min_el(root->left, k + 1, min, min_k);
    dfs_find_min_el(root->right, k + 1, min, min_k);
}

template <typename T>
void create_path_by_k(const Node<T> *root, const size_t row, size_t k, std::vector<std::string>& v) {
    static std::string s{};

    if (root == nullptr) {
        return;
    }

    s.push_back(root->data);

    if (k == row) {
        v.push_back(s);
        s.pop_back();
        return;
    }

    create_path_by_k(root->left, row, k + 1, v);
    create_path_by_k(root->right, row, k + 1, v);
    s.pop_back();
}

int main ()
{
    Node<char> *tree = nullptr;
    tree = new Node<char>{'a',
                            new Node<char>{'b',
                                new Node<char>{'d', nullptr, nullptr},
                                new Node<char>{'e',
                                    new Node<char>{'g', nullptr, nullptr},
                                    new Node<char>{'f', nullptr, nullptr}}},
                            new Node<char>{'c', nullptr, nullptr}};
//    dfs_print(tree, 0);
//    char minElInTree = 0x7F; // 0b01111111
//    size_t minLane = 0;
//    dfs_find_min_el(tree, 0, minElInTree, minLane);
//    cout << "the minimum element is: " << minElInTree << " , found on lane: " << minLane << endl;
    std::string myString{};
    std::vector<std::string> myVector{};
    create_path_by_k(tree, 2, 0,  myVector);
    create_path_by_k(tree, 3, 0,  myVector);

    for (auto i : myVector) {
        cout << i << " ";
    }

    return 0;
}
