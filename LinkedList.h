#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <typename T> class Node
{
public:
    Node *next;
    T data;

    Node(T data = T(), Node *next = nullptr)
    {
        this->data = data;
        this->next = next;
    }
};
template <typename T> class LinkedList {
private:
    int size;
    Node<T> *head;
public:
    LinkedList(T* items, const int count) : LinkedList()
    {
        if (count < 0 || items == nullptr)
        {
            throw std::invalid_argument("Invalid argument");
        }
        for (int i = 0; i < count; i++)
        {
            Append(items[i]);
        }
    }
    LinkedList()
    {
        this->size = 0;
        this->head = nullptr;
    }
    LinkedList(const LinkedList<T> &list) : LinkedList()
    {
        Node<T> *present = list.head;
        for (int i = 0; i < list.size; i++)
        {
            Append(present->data);
            present = present->next;
        }
        this->size = list.size;
    }
    ~LinkedList()
    {
        Node<T> *present = this->head;
        Node<T> *next;
        while (present != nullptr)
        {
            next = present->next;
            delete present;
            present = next;
        }
        this->size = 0;
    }
    T GetFirst()
    {
        if (head == nullptr)
        {
            throw std::invalid_argument("Index out of range");
        }
        return this->head->data;
    }
    T GetLast()
    {
        if (head == nullptr)
        {
            throw std::invalid_argument ("index out of range");
        }
        Node<T> *present = head;
        for (int i = 0; i < this->size - 1; i++)
        {
            present = present->next;
        }
        return present->data;
    }
    T Get(int index)
    {
        if (index < 0 || index >= this->size)
        {
            throw std::invalid_argument ("index out of range");
        }
        Node<T> *present = this->head;
        for (int i = 0; i < index; i++)
        {
            present = present->next;
        }
        return present->data;
    }
    LinkedList<T> *GetSubList (int startIndex, int endIndex)
    {
        if (startIndex < 0 || endIndex >= this->size || startIndex > endIndex || endIndex < 0)
        {
            throw std::invalid_argument ("index out of range");
        }
        LinkedList<T> *resultList = new LinkedList<T>();
        for (int i = startIndex; i < endIndex; i++)
        {
            resultList->Append(this->Get(i));
        }
        return resultList;
    }
    int GetLength() const
    {
        return this->size;
    }
    void Append(T item)
    {
        if (this->head == nullptr)
        {
            this->head = new Node<T>(item);
        }
        else
        {
            Node<T> *present = this->head;
            for (int i = 1; i < this->size; i++)
            {
                present = present->next;
            }
            present->next = new Node<T>(item);
        }
        size+=1;
    }
    void Prepend(T item)
    {
        Node<T> *newHead= new Node<T>(item);
        newHead->next = head;
        head = newHead;
        size+=1;
    }
    void InsertAt(T item, int index)
    {
        if (index < 0 || index >= this->size)
        {
            throw std::invalid_argument ("index out of range");
        }
        Node<T> *present = this->head;
        for (int i = 0; i < index - 1; i++)
        {
            present = present->next;
        }
        Node<T> *newItem = new Node<T>(item);
        newItem->next = present->next;
        present->next = newItem;
        this->size+=1;
    }
    LinkedList<T> *Concat (LinkedList<T> &list)
    {
        LinkedList<T> *resultList = new LinkedList<T>();
        for (int i = 0; i < this->size; i++)
        {
            resultList->Append(this->Get(i));
        }
        for (int i = 0; i < list.size; i++)
        {
            resultList->Append(list.Get(i));
        }
        return resultList;
    }
};

#endif
