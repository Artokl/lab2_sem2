#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H

#include <stdexcept>
#include "DynamicArray.h"
#include "Sequence.h"

template <typename T> class ArraySequence: public Sequence<T> {
protected:
    DynamicArray<T> *array;
    virtual ArraySequence<T> *GetInstance() = 0;
public:
    ArraySequence()
    {
        this->array = new DynamicArray<T>();
    }
    ArraySequence(T *items, int count)
    {
        this->array = new DynamicArray<T>(items, count);
    }
    ArraySequence(const ArraySequence<T> &seq)
    {
        this->array = new DynamicArray<T>(*seq.array);
    }
    ArraySequence(DynamicArray<T> *array)
    {
        this->array = array;
    }
    ArraySequence(const DynamicArray<T> &array)
    {
        this->array = new DynamicArray<T>(array);
    }
    ~ArraySequence() override
    {
        delete this->array;
    }
    T GetFirst() const override
    {
        return this->array->Get(0);
    }
    T GetLast() const override
    {
        return this->array->Get(this->array->GetSize() - 1);
    }
    T Get(int index) override
    {
        return this->array->Get(index);
    }
    int GetLength() override
    {
        return this->array->GetSize();
    }
    ArraySequence<T> *Append(T item) override
    {
        ArraySequence<T> *result = GetInstance();
        result->array->Set(item, result->array->GetSize());
        return result;
    }
    ArraySequence<T> *Prepend(T item) override
    {
        ArraySequence<T> *result = GetInstance();
        result->array->Set(item, 0);
        return result;
    }
    ArraySequence<T> *InsertAt(T item, int index) override
    {
        ArraySequence<T> *result = GetInstance();
        result->array->Set(item, index);
        return result;
    }
};
template <typename T> class MutableArraySequence : public ArraySequence<T>
{
private:
  ArraySequence<T> *GetInstance () override
  {
      return static_cast<ArraySequence<T> *> (this);
  }
public:
    using ArraySequence<T>::ArraySequence;
    MutableArraySequence<T> *Concat (Sequence<T> &list) override
    {
        MutableArraySequence<T> *presentResult = new MutableArraySequence<T> ();
        for (int i = 0; i < this->GetLength (); i++)
          {
              presentResult->Append (this->Get (i));
          }
        for (int i = 0; i < list.GetLength (); i++)
          {
              presentResult->Append (list.Get(i));
          }
        return presentResult;
    }
    MutableArraySequence<T> *GetSubSequence (int startIndex, int endIndex) override
    {
        if (startIndex < 0 || endIndex < 0 || startIndex >= this->array->GetSize() || endIndex < startIndex)
        {
            throw std::invalid_argument("Invalid argument");
        }
        MutableArraySequence<T> *presentResult = new MutableArraySequence<T> ();
        for (int i = startIndex; i <= endIndex; i++)
          {
              presentResult->Append (this->Get (i));
          }
        return presentResult;
    }
};

template <typename T> class ImmutableArraySequence : public ArraySequence<T>
{
private:
    ArraySequence<T> *GetInstance () override
    {
        ImmutableArraySequence<T> *result = new ImmutableArraySequence (this->GetLength ());
        for (int i = 0; i < this->GetLength (); i++)
        {
            result->array[i] = this->array[i];
        }
        return result;
    }
public:
    using ArraySequence<T>::ArraySequence;
    ImmutableArraySequence<T> *Concat (Sequence<T> &array) override
    {
        MutableArraySequence<T> *present = new MutableArraySequence<T> ();
        for (int i = 0; i < this->GetLength (); i++)
        {
            present->Append (this->Get (i));
        }
        for (int i = 0; i < array.GetLength (); i++)
        {
            present->Append (array.Get (i));
        }
        ImmutableArraySequence<T> *result = new ImmutableArraySequence<T> ();
        for (int i = 0; i < present->GetLength (); i++)
        {
            result->Append (present->Get (i));
        }
        delete present;
        return result;
    }
    ImmutableArraySequence<T> *GetSubSequence (int startIndex, int endIndex) override
    {
        if (startIndex < 0 || endIndex < startIndex || endIndex >= this->GetLength ())
        {
            throw std::invalid_argument ("invalid argument");
        }
        MutableArraySequence<T> *present = new MutableArraySequence<T> ();
        for (int i = startIndex; i <= endIndex; i++)
        {
            present->Append (this->Get (i));
        }
        ImmutableArraySequence<T> *result = new ImmutableArraySequence<T> ();
        for (int i = 0; i < present->GetLength (); i++)
        {
            result->Append (present->Get (i));
        }
        delete present;
        return result;
    }
};
#endif //ARRAYSEQUENCE_H
