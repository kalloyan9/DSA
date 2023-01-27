#include <iostream>
#include <vector>
#include <queue>
using namespace std;

template <typename T>
struct TNode { T data; std::vector<TNode*> children; };

template <typename T>
bool ordered_levels(TNode<T> *t) {
    queue<TNode<T>*> q;
    TNode<T> *temp = nullptr;

    // use BFS and delimiter nullptr between levels
    q.push(t);
    q.push(nullptr);
    while (!q.empty()) {
        temp = q.front();
        q.pop();

        if (nullptr == temp) {
            if (!q.size()) {
                break;
            } else {
                q.push(nullptr);
            }
        } else {
            vector<TNode<T>*> v = temp->children;
            if (v.size()) {
                TNode<T> *prev = v[0];
                for (size_t i = 0; i < v.size(); ++i) {
                    if (prev->data > v[i]->data) {
                        return false;
                    }
                    q.push(v[i]);
                }
            }
        }
    }
    return true;
}

int main() {

    TNode<int> *t1 = new TNode<int> {0,{
                                 new TNode<int> {1,{
                                                 new TNode<int>{-1,{}},
                                                 new TNode<int>{1,{}}
                                 }},
                                 new TNode<int> {2,{
                                                 new TNode<int>{5,{
                                                                new TNode<int>{7,{}},
                                                                new TNode<int>{8,{}}
                                                 }}
                                 }},
                                 new TNode<int> {3,{}}
                 }};

    TNode<int> *t4 = new TNode<int> {0,{
                 new TNode<int> {1,{
                                 new TNode<int>{-1,{}},
                                 new TNode<int>{1,{}}
                 }},
                 new TNode<int> {2,{
                                 new TNode<int>{5,{
                                                new TNode<int>{8,{}},
                                                new TNode<int>{7,{}}
                                 }}
                 }},
                 new TNode<int> {3,{}}
    }};
    cout << ordered_levels(t1) << endl;
    cout << ordered_levels(t4) << endl;

    return 0;
}
