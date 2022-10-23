#include <iostream>
#include <new>

template <typename T>
struct Stack {

struct Node {
    T data;
    Node *prev;
};

bool empty() const {
    return nullptr == tos;
}

unsigned size_linear() {
    unsigned counter = 0;
    Node *ptr = tos;
    while (ptr != nullptr) {
        ++counter;
        ptr = ptr->prev;
    }
    return counter;
}

unsigned size() const {
    return _size;
}

T top() {
    if (nullptr == tos) {
        throw std::underflow_error("Empty stack");
    }
    return tos->data;
}

void push(T data) {
    Node *keep = new (std::nothrow) Node;
    keep->data = data;
    keep->prev = tos;
    tos = keep;
    ++_size;
}

void pop() {
    if (tos != nullptr) {
        Node *keep = tos;
        tos = tos->prev;
        --_size;
    }
}

// data:
    Node *tos = nullptr;
    unsigned _size = 0;
};

int main () {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    std::cout << s.size() << std::endl;

    s.push(4);
    std::cout << s.top() << std::endl;
    s.push(5);
    s.push(6);
    s.pop();
    std::cout << s.top() << std::endl;
    s.pop();
    std::cout << s.top() << std::endl;
    s.pop();
    std::cout << s.top() << std::endl;
    s.pop();
    std::cout << s.top() << std::endl;


    std::cout << s.size_linear() << std::endl;


    return 0;
}
