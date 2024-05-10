#ifndef LISTSEQUENCE_H
#define LISTSEQUENCE_H

#include <stdexcept>
#include "Sequence.h"
#include "LinkedList.h"

template <typename T> class ListSequence: public Sequence<T>
{
protected:
    LinkedList<T> *list;
    virtual ListSequence<T> *GetInstance() = 0;
public:
    ListSequence()
    {
        this->list = new LinkedList<T>();
    }
    ListSequence(T *items, int count)
    {
        this->list = new LinkedList<T>(items, count);
    }
    ListSequence(const ListSequence<T> &seq)
    {
        this->list = new LinkedList<T>(*seq.list);
    }
    ListSequence(LinkedList<T> *list)
    {
        this->list = list;
    }
    ListSequence (const LinkedList<T> &list)
    {
        this->list = new LinkedList<T>(list);
    }
    ~ListSequence()
    {
        delete this->list;
    }
    T GetFirst() const override
    {
        return this->list->GetFirst();
    }
    T GetLast() const override
    {
        return this->list->GetLast();
    }
    T Get(int index) override
    {
        return this->list->Get(index);
    }
    int GetLength() override
    {
        return this->list->GetLength();
    }
    ListSequence<T> *Append(T item) override
    {
        ListSequence<T> *result = GetInstance();
        result->list->Append(item);
        return result;
    }
    ListSequence<T> *Prepend(T item) override
    {
        ListSequence<T> *result = GetInstance();
        result->list->Prepend(item);
        return result;
    }
    ListSequence<T> *InsertAt(T item, int index) override
    {
        ListSequence<T> *result = GetInstance();
        result->list->InsertAt(item, index);
        return result;
    }
};

template <typename T> class MutableListSequence : public ListSequence<T>
{
private:
    ListSequence<T> *GetInstance() override
    {
        return static_cast<ListSequence<T> *>(this);
    }
public:
    using ListSequence<T>::ListSequence;
    MutableListSequence<T> *Concat(Sequence<T> &array) override
    {
        MutableListSequence<T> *result = new MutableListSequence<T>;
        for (int i = 0; i < this->GetLength(); i++)
        {
            result->Append(this->Get(i));
        }
        for (int i = 0; i < array.GetLength(); i++)
        {
            result->Append(array.Get(i));
        }
        return result;
    }
    MutableListSequence<T> *GetSubSequence(int startIndex, int endIndex) override
    {
        if (startIndex < 0 || endIndex < startIndex || endIndex >= this->GetLength())
        {
            throw std::invalid_argument("invalid argument");
        }
        T *present = new T[endIndex - startIndex + 1];
        for (int i = startIndex; i <= endIndex; i++)
        {
            present[i-startIndex] = this->Get(i);
        }
        MutableListSequence<T> *result = new MutableListSequence<T>(present, endIndex - startIndex + 1);
        delete[] present;
        return result;
    }
};

template <typename T> class ImmutableListSequence : public ListSequence<T>
{
private:
    ListSequence<T> *GetInstance() override
    {
        ImmutableListSequence<T> *result = new ImmutableListSequence<T>(*this);
        return result;
    }

public:
    using ListSequence<T>::ListSequence;

    ImmutableListSequence<T> *Concat(Sequence<T> &array) override
    {
        MutableListSequence<T> *present = new MutableListSequence<T>;
        for (int i = 0; i < array.GetLength(); i++)
        {
            present->Append(array.Get(i));
        }
        ImmutableListSequence<T> *result = new ImmutableListSequence<T>();
        for (int i = 0; i < present->GetLength (); i++)
        {
            result->Append (present->Get (i));
        }
        delete present;
        return result;
    }

    ImmutableListSequence<T> *GetSubSequence(int startIndex, int endIndex) override
    {
        if (startIndex < 0 || endIndex < startIndex || endIndex >= this->GetLength())
        {
            throw std::invalid_argument("invalid argument");
        }
        LinkedList<T> *resultList = this->list->GetSubList(startIndex, endIndex);
        ImmutableListSequence<T> *result = new ImmutableListSequence<T>(resultList);
        result->list = resultList;
        return result;
    }
};

/*
template <typename T> class MutableListSequence : public ListSequence<T>
{
private:
    ListSequence<T> *GetInstance() override
    {
        return static_cast<ListSequence<T> *> (this);
    }
public:
    using ListSequence<T>::ListSequence;
    MutableListSequence<T> *Concat(Sequence<T> &seq) override
    {
        for (int i = 0; i < seq.GetLength(); i++)
        {
            this->Append(seq.Get(i));
        }
        return this;
    }
    MutableListSequence<T> *GetSubSequence(int startIndex, int endIndex) override
    {
        if (startIndex < 0 || endIndex < 0 || startIndex >= this->list->GetLength() || endIndex < startIndex)
        {
            throw std::invalid_argument("Invalid argument");
        }
        LinkedList<T> *resultList = this->list->GetSubList(startIndex, endIndex);
        MutableListSequence<T> *result = new MutableListSequence<T>(resultList);
        result->list = resultList;
        return result;
    }
};

template <typename T> class ImmutableListSequence : public ListSequence<T>
{
private:
    ListSequence<T> *GetInstance() override
    {
        ImmutableListSequence<T> *instance = new ImmutableListSequence<T> (*this);
        return instance;
    }

public:
    using ListSequence<T>::ListSequence;
    ImmutableListSequence<T> *Concat(Sequence<T> &seq) override
    {
        LinkedList<T> *resultList = new LinkedList<T>;
        for (int i = 0; i < this->GetLength(); i++)
        {
            resultList->Append(this->Get(i));
        }
        for (int i = 0; i < seq.GetLength(); i++)
        {
            resultList->Append(seq.Get(i));
        }
        ImmutableListSequence<T> *result = new ImmutableListSequence<T>(resultList);
        return result;
    }
    ImmutableListSequence<T> *GetSubSequence(int startIndex, int endIndex) override
    {
        if (startIndex < 0 || endIndex < 0 || startIndex >= this->list->GetLength() || endIndex < startIndex)
        {
            throw std::invalid_argument("Invalid argument");
        }
        LinkedList<T> *resultList = this->list->GetSubList(startIndex, endIndex);
        ImmutableListSequence<T> *result = new ImmutableListSequence<T>(resultList);
        result->list = resultList;
        return result;
    }
};
*/
#endif //LISTSEQUENCE_H
