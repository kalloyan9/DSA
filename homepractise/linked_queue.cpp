#include <iostream>
#include <new>

template <typename T>
struct Queue {

struct Node {
    T data;
    Node *next;
};

bool isEmpty() const {
    return 0u == _size;
}

unsigned size() const {
    return _size;
}

T front() {
    if (nullptr == _begin) {
        throw std::underflow_error("Empty queue");
    }
    return _begin->data;
}

T back() {
    if (nullptr == _end) {
        throw std::underflow_error("Empty queue");
    }
    return _end->data;
}

void push_back(T data) {
    Node *keep = new (std::nothrow) Node;
    keep->data = data;
    keep->next = nullptr;
    if (isEmpty()) {
        _begin = keep;
        _end = keep;
    } else {
        _end->next = keep;
        _end = _end->next;
    }
    ++_size;
}

void pop() {
    if (nullptr != _begin) {
        Node *keep = _begin;
        _begin = _begin->next;
        --_size;
        delete keep;
    }
}

// data:
    Node *_begin = nullptr, *_end = nullptr;
    unsigned _size = 0;
};

int main () {
    Queue<int> q;
    q.push_back(1);
    q.push_back(2);
    q.push_back(3);
    q.push_back(4);
    q.push_back(5);

    std::cout << q.size() << std::endl;

    q.pop();
    std::cout << q.back() << std::endl;
    q.pop();
    std::cout << q.front() << std::endl;
    q.pop();
    std::cout << q.front() << std::endl;
    q.pop();
    std::cout << q.front() << std::endl << q.back() << std::endl;


    return 0;
}
