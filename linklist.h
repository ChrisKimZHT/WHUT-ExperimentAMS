#ifndef EXPERIMENTAMS_LINKLIST_H
#define EXPERIMENTAMS_LINKLIST_H

template<typename T>
class linklist_node
{
public:
    T data;
    linklist_node<T> *next;
};

template<typename T>
class linklist : public linklist_node<T>
{
private:
    linklist_node<int> *head{};
public:
    linklist();
    bool empty();
    int size();
    void push_front(T);
    void push_back(T);
    void insert(int, T);
    void erase(int);
    void print();
    T &operator[](int);
};


#endif //EXPERIMENTAMS_LINKLIST_H
