#define DOCTEST_CONFIG_IMPLEMENT
#include "../../libs/doctest.h"
#include "../../libs/treeutils.cpp"

#include <iostream>
#include <vector>
/*
======================
Решение на задачата:
======================
*/


template <typename T>
struct Node {
    T _data;
    Node *_left, *_right;

    Node(T data, Node *left, Node *right) {
        _data = data;
        _left = left;
        _right = right;
    }
};

/*
INDUKTIVNA DEFINICIA ZA DOPULVANE NA DURVO (neformalno):
Dadeni sa durvo t1 i t2.
Razglejdame durvetata ednovremenno i rekursivno po niva.
Za vseki vruh ot t2 za koito ne sushtestvuva biekciq s vruh ot t1, kazvame che se dopulva,
kato dobavqem poddurvoto s biektivniq vruh ot t1.
*/

template <typename T>
void expand(box<T> *t1, box<T> *&t2) {
    if (nullptr == t1) {
        return;
    }

    if (nullptr == t2) {
        t2 = t1;
        return;
    }

    expand(t1->left, t2->left);
    expand(t1->right, t2->right);
}

// dev tests:
template <typename T>
void print_dfs(box<T> *root) {
    if (nullptr == root) {
        return;
    }

    std::cout << root->data;
    print_dfs(root->left);
    print_dfs(root->right);
}



/*
======================
Тестове
======================
*/




TEST_CASE("Test Edges")
{
     box<int> *t1=nullptr,
              *t2=nullptr,
              *t3=nullptr;

    setAt(t1,"",0);
    setAt(t3,"",0);

    expand(t2,t1);
    CHECK(tree_equals(t1,t3));

    expand(t1,t2);
    CHECK(tree_equals(t2,t1));

}

TEST_CASE("Test Expand")
{
    box<int> *t1=nullptr,
             *t2=nullptr,
             *t3=nullptr;

    setAt(t1,"",10);
    setAt(t1,"L",20);
    setAt(t1,"R",30);
    setAt(t1,"RL",40);
    setAt(t1,"RLL",70);
    setAt(t1,"RR",50);
    setAt(t1,"RRL",60);

    setAt(t2,"",0);
    setAt(t2,"R",0);
    setAt(t2,"RL",80);
    setAt(t2,"RLL",90);
    setAt(t2,"RLR",95);

    setAt(t3,"",0);
    setAt(t3,"R",0);
    setAt(t3,"RL",80);
    setAt(t3,"RLL",90);
    setAt(t3,"RLR",95);
    setAt(t3,"L",20);
    setAt(t3,"RR",50);
    setAt(t3,"RRL",60);

    expand(t1,t2);
    CHECK(tree_equals(t2,t3));

}


int main()
{


 doctest::Context().run();

 return 0;
}
