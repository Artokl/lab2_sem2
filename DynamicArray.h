#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <iostream>

template <typename T> class DynamicArray
{
private:
    int size{};
    T *elements;
    int capacity{};

    void Reserve (int newCapacity) {
        if (newCapacity <= capacity)
        {
            capacity = newCapacity;
            return;
        }

        T *newElements = new T[newCapacity];
        for (int i = 0; i < size; i++)
        {
            newElements[i] = elements[i];
        }
        delete elements;
        elements = newElements;
        capacity = newCapacity;
    }

public:
    DynamicArray ()
    {
        this->size = 0;
        this->capacity = 0;
        this->elements = nullptr;
    }
    DynamicArray (T *items, int count) : DynamicArray (count)
    {
        if (items == nullptr)
        {
            throw std::out_of_range ("invalid elems argument for constructor");
        }
        for (int i = 0; i < count; i++)
        {
            this->elements[i] = items[i];
        }
    }
    DynamicArray (int size) : DynamicArray()
    {
        this->size = size;
        this->capacity = size+1;
        this->elements = nullptr;
        if (size < 0)
        {
            throw std::out_of_range ("invalid size argument");
        }
        this->elements = new T[capacity];
    }
    DynamicArray (const DynamicArray<T> &dynamicArray) : DynamicArray<T> (dynamicArray.elements, dynamicArray.size)
    {
    }
    ~DynamicArray ()
    {
        delete[] this->elements;
        this->size = 0;
    }
    T Get (int index)
    {
        if (index < 0 || index > this->size)
        {
            throw std::out_of_range ("invalid argument");
        }
        return this->elements[index];
    }
    int GetSize() const
    {
        return this->size;
    }
    void Set (const T &value, int index)
    {
        if (index < 0 || index > this->size)
        {
            throw std::out_of_range ("invalid argument");
        }
        Resize (size + 1);
        for (int i = size; i > index; i--)
        {
            elements[i] = elements[i - 1];
        }
        elements[index] = value;
    }
    void Resize (int newSize)
    {
        if (newSize < 0)
        {
            throw std::out_of_range ("invalid argument");
        }
        if (newSize == 0)
        {
            delete[] this->elements;
            this->elements = nullptr;
            this->capacity = 0;
        }
        else if (newSize >= this->capacity)
        {
            Reserve (newSize * 2);
        }
        else if (newSize < this->size)
        {
            T *Newelements = new T[newSize];
            for (int i = 0; i < newSize; i++)
            {
                Newelements[i] = this->elements[i];
            }
            delete[] this->elements;
            this->elements = Newelements;
            this->capacity = newSize;
        }
        this->size = newSize;
    }
};

#endif
