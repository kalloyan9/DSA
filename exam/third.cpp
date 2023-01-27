#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

struct TNode
{
    std::pair<std::string,int> data;
    TNode *left, *right;
};

void create_tree_helper_rec(TNode *&root, size_t l, size_t r, vector<pair<string,int>> &v) {
    if (l >= r) {
        return;
    }

    size_t mid = (l + r) / 2;
    root = new TNode;
    root->data = v[mid];
    root->left = nullptr;
    root->right = nullptr;

    create_tree_helper_rec(root->left, l, mid, v);
    create_tree_helper_rec(root->right, mid + 1, r, v);
}

TNode* create_tree(const std::string& s) {
    map<string, size_t> m;
    string key;
    const char *p1 = &s[0], *p2;
    while (*p1 != '\0') {
        // extract all words
        while (*p1 != '\0' && *p1 != ' ') {
            key.push_back(*p1);
            ++p1;
        }

        // increment value in the map
        ++m[key];

        key.clear();
        ++p1;
    }

    // storing in vector alphabetical order is guaranteed by iterating the map
    vector<pair<string, int>> v;
    for (pair<string, int> it : m) {
        v.push_back(it);
    }

    // algorithm: create binary tree from ordered vector
    size_t l = 0, r = v.size(), mid = (l + r) / 2;
    TNode *root = nullptr;
    if (!v.size()) {
        return root;
    } else {
        create_tree_helper_rec(root, l, r, v);
        return root;
    }
}

void print_tree_rec(TNode *root) {
    if (!root) {
        return;
    }

    cout << root->data.first << ", " << root->data.second << endl;
    print_tree_rec(root->left);
    print_tree_rec(root->right);
}


int main ()
{
    string t;
    getline(cin, t);

    print_tree_rec(create_tree(t));


    return 0;
}
