#define DOCTEST_CONFIG_IMPLEMENT
#include "../../libs/doctest.h"
#include "../../libs/treeutils.cpp"

#include <iostream>
#include <vector>
#include <queue>

/*
======================
Решение на задачата:
======================
*/

static constexpr int MAX_K = 100000;

template <typename T>
struct Node {
    T data;
    Node *left, *right;

    Node(T data, Node *left, Node *right) {
        this->data = data;
        this->left = left;
        this->right = right;
    }
};

template <typename T>
void dfs_store_in_helper(box<T> *root, int k, std::vector<T> storage_vector[]){

    if (root == nullptr || k >= MAX_K) {
        return;
    }

    storage_vector[k].push_back(root->data);

    dfs_store_in_helper(root->right, k+1, storage_vector);
    dfs_store_in_helper(root->left, k+1, storage_vector);
}


template <typename T>
std::vector<T> levelsGrowing(box<T> *t) {
    if (nullptr == t) {
        return {};
    }

    static std::vector<T> storage_vector[MAX_K]; // static to init it only once
    static std::vector<T> final_vector;
    for (int i = 0; i < MAX_K; ++i) {
        storage_vector[i].clear();
    }
    final_vector.clear();

    dfs_store_in_helper(t, 0, storage_vector);

    int last_size = 0;
    for (int i = 0; i < MAX_K; ++i) {
        int curr_size = storage_vector[i].size();
        if (0 == curr_size) {
            break;
        }

        if (curr_size > last_size) {
            for (auto j : storage_vector[i]) {
                final_vector.push_back(j);
            }
            last_size = curr_size;
        }

    }

    return final_vector;
}


/*
======================
Тестове
======================
*/

TEST_CASE("Test Edges")
{
    box<int> *t=nullptr;

    CHECK(levelsGrowing(t).size()==0);

    setAt(t,"",10);

    CHECK(levelsGrowing(t).size()==1);
}



TEST_CASE("Test Levels Growing")
{
    box<int> *t=nullptr;

    setAt(t,"",10);
    setAt(t,"L",20);
    setAt(t,"R",30);
    setAt(t,"RL",40);
    setAt(t,"RR",50);
    setAt(t,"RRL",60);
    setAt(t,"RLL",70);
    setAt(t,"RRR",80);

    std::vector<int> expected = {10, 30, 20, 80, 60, 70};
    auto res = levelsGrowing(t);
    CHECK(res.size() == expected.size());
    CHECK(res == expected);
}



int main()
{
// dev test compiling
//    Node<int> *a = nullptr;
//    levelsGrowing(a);
    doctest::Context().run();
    return 0;
}
