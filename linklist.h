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
    int list_size{};
    linklist_node<T> *head{};
public:
    linklist()
    {
        this->head = new linklist_node<T>;
        this->list_size = 0;
        this->head->next = nullptr;
    }
    bool empty()
    {
        if (this->head->next == nullptr)
            return true;
        else
            return false;
    }
    int size()
    {
        return this->list_size;
    }
    void push_front(T data)
    {
        auto *new_node = new linklist_node<T>;
        new_node->data = data;
        new_node->next = this->head->next;
        this->head->next = new_node;
        this->list_size++;
    }
    void push_back(T data)
    {
        auto *new_node = new linklist_node<T>;
        new_node->data = data;
        new_node->next = nullptr;
        auto *tail = this->head;
        for (int i = 0; i < this->size(); i++)
            tail = tail->next;
        tail->next = new_node;
        this->list_size++;
    }
    void insert(int idx, T data)
    {
        auto *pos = this->head;
        for (int i = 0; i <= idx; i++)
            pos = pos->next;
        auto *new_node = new linklist_node<T>;
        new_node->data = data;
        new_node->next = pos->next;
        pos->next = new_node;
        this->list_size++;
    }
    void erase(int idx)
    {
        auto *pos = this->head;
        for (int i = 0; i < idx; i++)
            pos = pos->next;
        linklist_node<T> *del = pos->next;
        pos->next = del->next;
        delete del;
        this->list_size--;
    }
//    void print()
//    {
//        for (auto p = this->head->next; p != nullptr; p = p->next)
//            cout << p->data << ' ';
//        cout << endl;
//    }
    void clear()
    {
        linklist_node<T> *del = nullptr;
        while (head->next != nullptr)
        {
            del = head->next;
            head->next = del->next;
            delete del;
        }
        this->list_size = 0;
    }
    T &operator[](int idx)
    {
        auto *pos = this->head;
        for (int i = 0; i <= idx; i++)
            pos = pos->next;
        return pos->data;
    }
};

#endif //EXPERIMENTAMS_LINKLIST_H
