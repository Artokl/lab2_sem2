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
    virtual ~ArraySequence() override
    {
        delete this->array;
    }
    T GetFirst() override
    {
        return this->array->Get(0);
    }
    T GetLast() override
    {
        return this->array->Get(this->array->GetSize() - 1);
    }
    T Get(int index) const override
    {
        return this->array->Get(index);
    }
    int GetLength() const override
    {
        return this->array->GetSize();
    }
    ArraySequence<T> *Append(T item) override
    {
        ArraySequence<T> *result = GetInstance();
        result->array->Resize(result->array->GetSize() + 1);
        result->array->Set(result->array->GetSize() - 1, item);
        return result;
    }
    ArraySequence<T> *Prepend(T item) override
    {
        ArraySequence<T> *result = GetInstance();
        result->array->Resize(result->array->GetSize() + 1);
        T current = this->array->Get(0);
        for (int i = result->array->GetSize() - 1; i > 0; --i)
        {
            result->array->Set(i, result->array->Get(i - 1));
        }
        result->array->Set(0, item);
        return result;
    }
    ArraySequence<T> *InsertAt(T item, int index) override
    {
        ArraySequence<T> *result = GetInstance();
        result->array->Resize(this->array->GetSize() + 1);
        for (int i = result->array->GetSize() - 1; i > index; --i)
        {
            result->array->Set(i, result->array->Get(i - 1));
        }
        result->array->Set(index, item);
        return result;
    }
};
template <typename T> class MutableArraySequence : public ArraySequence<T>
{
private:
  ArraySequence<T> *
  GetInstance () override
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
      MutableArraySequence<T> *presentResult = new MutableArraySequence ();
      for (int i = 0; i <= endIndex - startIndex; i++)
        {
            presentResult->Append (this->Get (startIndex + i - 1));
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
      if (startIndex < 0 || endIndex < startIndex
          || endIndex >= this->GetLength ())
        {
          throw std::invalid_argument ("invalid argument");
        }
      ImmutableArraySequence<T> *result = new ImmutableArraySequence<T> (&(*(this->array))[startIndex], endIndex - startIndex + 1);
      return result;
  }
};
#endif //ARRAYSEQUENCE_H
