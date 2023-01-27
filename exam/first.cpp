#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    T data;
    Node *next;
};

template <typename T>
T most_common (Node<T> *l) {
    Node<T> *ans = nullptr;
    size_t count, bestCount = 0;
    Node<T> *start = l;
    while (nullptr != start) {
        count = 0;
        for (Node<T> *i = start; nullptr != i; i = i->next) {
            if (*i == *start) {
                ++count;
            }
        }
        if (count > bestCount) {
            bestCount = count;
            ans = start;
        }
        ++start;
    }
    return *start;
}

int main() {

    return 0;
}
