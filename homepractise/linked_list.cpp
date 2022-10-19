/**
12.1. Да се реализира метод int LList<T>::count(int x), който преброява
колко пъти елементът x се среща в списъка.
12.2. Да се реализира конструктор с два аргумента x и y от тип int. Конс-
трукторът създава списък с елементи x, x + 1, ..., y, при положение, че
x ≤ y.
56
12.3. Да се реализира метод LList<T>::push_back за добавяне на елемент от
тип T към края на списъка.
12.4. Да се реализира метод оператор LList<T>::operator += за добавяне на
елемент от тип T към края на списъка.
12.7. Да се реализира метод l1.append(l2), която добавя към края на списъка
l1 всички елементи на списъка l2.
*/

#include <iostream>
#include <new>

template <typename T>
struct linked_list {

struct Node {
    T data;
    Node *next;
};

void push(T const&element) {
    Node *temp = new (std::nothrow) Node;
    temp->data = element;
    temp->next = nullptr;

    if (nullptr == head) {
        head = temp;
    } else {
        Node *last = head;
        while (last->next != nullptr) {
            last = last->next;
        }
        last->next = temp;
    }
}

linked_list& operator+= (T const&rhs) {
    Node *temp = new (std::nothrow) Node;
    temp->data = rhs;
    temp->next = nullptr;

    if (nullptr == head) {
        head = temp;
    } else {
        Node *last = head;
        while (last->next != nullptr) {
            last = last->next;
        }
        last->next = temp;
    }
    return *this;
}

void remove(T const&element) {
    Node *temp = head;
    while (temp->next != nullptr && temp->next->data != element) {
        temp = temp->next;
    }
    if (temp->next != nullptr) {
        Node *pivot = temp->next;
        temp->next = pivot->next;
        delete pivot;
    }
}

void traverse() {
    Node *temp = head;
    while (temp != nullptr) {
        std::cout << temp->data;
        temp = temp->next;
    }
}

unsigned size() {
    unsigned result = 0u;
    Node *temp = head;
    while (temp != nullptr) {
        ++result;
        temp = temp->next;
    }
    return result;
}

Node* find(T const&element) {
    Node *temp = head;
    while (temp->next != nullptr && temp->next->data != element) {
        temp = temp->next;
    }
    Node *pivot = temp->next;
    return pivot;
}

unsigned count(T const&element) {
    unsigned counter = 0u;
    Node *temp = head;
    while (temp->next != nullptr) {
        if (element == temp->data) {
            ++counter;
        }
        temp = temp->next;
    }
    return counter;
}

void append(linked_list<T> second_linked_list) {
    Node *temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = second_linked_list.head;
}

// data
Node *head = nullptr;
};

linked_list<int> list_counter;
void construct_linked_list_counter(int from, int to) {
    for (int i = from; i <= to; ++i) {
        list_counter.push(i);
    }
    list_counter.traverse();
    std::cout << std::endl;
}

int main ()
{
    construct_linked_list_counter(7, 9);

    linked_list<int> llist;
    llist.push(1);
    llist.push(2);
    llist.push(3);
    llist.push(4);
    llist.traverse();
    std::cout << std::endl;

    llist.append(list_counter);
    llist.traverse();
    std::cout << std::endl;
    llist.remove(9);
    llist.traverse();
    std::cout << std::endl;
    llist+=(5);
    llist.traverse();
    std::cout << std::endl;



    return 0;
}
