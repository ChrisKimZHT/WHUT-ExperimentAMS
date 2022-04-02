#include <iostream>
#include "linklist.h"

using namespace std;

template<typename T>
linklist<T>::linklist()
{
    this->head = new linklist_node<T>;
    this->head->data = 0;
    this->head->next = nullptr;
}

template<typename T>
bool linklist<T>::empty()
{
    if (this->head->next == nullptr)
        return true;
    else
        return false;
}

template<typename T>
int linklist<T>::size()
{
    return this->head->data;
}

template<typename T>
void linklist<T>::push_front(T data)
{
    auto *new_node = new linklist_node<T>;
    new_node->data = data;
    new_node->next = this->head->next;
    this->head->next = new_node;
    this->head->data++;
}

template<typename T>
void linklist<T>::push_back(T data)
{
    auto *new_node = new linklist_node<T>;
    new_node->data = data;
    new_node->next = nullptr;
    auto *tail = this->head;
    for (int i = 0; i < this->size(); i++)
        tail = tail->next;
    tail->next = new_node;
    this->head->data++;
}

template<typename T>
void linklist<T>::insert(int idx, T data)
{
    auto *pos = this->head;
    for (int i = 0; i <= idx; i++)
        pos = pos->next;
    auto *new_node = new linklist_node<T>;
    new_node->data = data;
    new_node->next = pos->next;
    pos->next = new_node;
    this->head->data++;
}

template<typename T>
void linklist<T>::erase(int idx)
{
    auto *pos = this->head;
    for (int i = 0; i < idx; i++)
        pos = pos->next;
    linklist_node<T> *del = pos->next;
    pos->next = del->next;
    delete del;
    this->head->data--;
}

template<typename T>
void linklist<T>::print()
{
    for (auto p = this->head->next; p != nullptr; p = p->next)
        cout << p->data << ' ';
    cout << endl;
}

template<typename T>
T &linklist<T>::operator[](int idx)
{
    auto *pos = this->head;
    for (int i = 0; i <= idx; i++)
        pos = pos->next;
    return pos->data;
}
