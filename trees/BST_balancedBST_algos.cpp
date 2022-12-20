/*
1. algo convert BST into Balanced BST
2. Find nodes which are at a distance k from root in a BT
3. Find if a given BT is a sub-tree of another BT
4. Counting subtrees where nodes sum to a specific data.
5. Invert / Reverse BT.
6. Convert BT to BST.
*/

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node *left, *right;
};

// balanced binary search tree from binary search tree
template <typename T>
void saveTree(Node<T>* root, std::vector<Node<T>*>& v) {
    if (nullptr == root) {
        return;
    }

    saveTree(root->left, v);
    v.push_back(root);
    saveTree(root->right, v);
}

template <typename T>
Node<T>* balanceTreeHelper(std::vector<Node<T>*>& v, int start, int end) {
    if (start > end) {
        return nullptr;
    }

    int midIndex = (end + start) / 2;
    Node<T>* root = v[midIndex];
    root->left = balanceTreeHelper(v, start, midIndex-1);
    root->right = balanceTreeHelper(v, midIndex+1, end);
    return root;
}

template <typename T>
void balanceTree(Node<T>*& root)
{
    std::vector<Node<T>*> v;
    saveTree(root, v);
    int end = v.size() - 1;
    root = balanceTreeHelper(v, 0, end);
}

// find nodes at distance k (at level K)
template <typename T>
void findAtDistanceK(Node<T> *root, int k) {
    if (nullptr == root) {
        return;
    }

    if (0 == k) {
        std::cout << root->data << " ";
        return;
    }

    findAtDistanceK(root->left, k - 1);
    findAtDistanceK(root->right, k - 1);
}

// find subtree
template <typename T>
bool areIdentical(Node<T> *source, Node<T> *subtree) {
    if (nullptr == source && nullptr == subtree)
        return true;

    if (nullptr == source || nullptr == subtree) {
        return false;
    }

    return (source->data == subtree->data
            && areIdentical(source->left, subtree)
            && areIdentical(source->right, subtree));
}

template <typename T>
bool isSubtree(Node<T> *source, Node<T> *subtree) {
    if (nullptr == subtree) {
        return true;
    }

    if (nullptr == source) {
        return false;
    }

    if (areIdentical(source, subtree)) {
        return true;
    }

    return isSubtree(source->left, subtree) || isSubtree(source->right, subtree);
}

// count subtrees where nodes sum to a given value
template <typename T>
int sumTree(Node<T> *root) {
    if (nullptr == root) {
        return 0;
    }

    return root->data + sumTree(root->left) + sumTree(root->right);
}

template <typename T>
int countSubTreesSumK(Node<T> *root, int k) {
    if (nullptr == root) {
        return 0;
    }

    if (sumTree(root) == k) {
        return 1 + countSubTrees(root->left, k) + countSubTrees(root->right, k);
    }

    return countSubTrees(root->left, k) + countSubTrees(root->right, k);
}

// reverse BST / invert / mirroring:
template <typename T>
void reverseBST(Node<T> *root, Node<T> *reverse) {
    if (nullptr == root) {
        return;
    }

    // swap left and right recursive
    Node<T> *temp = root->left;
    root->left = root->right;
    root->right = temp;
    reverse(root->left);
    reverse(root->right);
}

// convert BT to BST.
// put in vector and build tree from it.
// if we want it to be balanced sort the vector.
template <typename T>
void insertIntoBST(Node<T>*& root, const T& value) {
    if (nullptr == root) {
        root = new Node<T>{value, nullptr, nullptr};
        return;
    }

    if (value < root->data) {
        insertIntoBST(root->left, value);
    } else if (value > root->data) {
        insertIntoBST(root->right, value);
    } else {
        // no duplication of nodes in BST definition.
        return;
    }
}

template <typename T>
void deleteBST(Node<T>*& root) {
    if (nullptr == root) {
        return;
    }

    if (nullptr == root->left && nullptr == root->right) {
        delete root;
        root = nullptr;
        return;
    }

    deleteBST(root->left);
    deleteBST(root->right);
}

template <typename T>
void convertToBSTHelper(Node<T>* root, Node<T>*& result) {
    if (nullptr == root) {
        return;
    }

    insertIntoBST(result, root->data);
    convertToBSTHelper(root->left, result);
    convertToBSTHelper(root->right, result);
}

template <typename T>
void convertToBST(Node<T>*& root) {
    Node<T>* result = nullptr;
    convertToBSTHelper(root, result);

    deleteBST(root);
    root = result;
}

int main ()
{

    return 0;
}
