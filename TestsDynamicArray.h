#ifndef TESTSDYNAMICARRAY_H
#define TESTSDYNAMICARRAY_H

#include "DynamicArray.h"
#include "assert.h"

void TestDynamicArrayConstructors()
{
    int a[] = {0, 872, 367, 412, 521};
    DynamicArray<int> test1(5);
    assert(test1.GetSize() == 5);
    DynamicArray<int> test2(a, 5);
    assert(test2.GetSize() == 5);
    for (int i = 0; i < test2.GetSize(); i++)
    {
        assert(test2.Get(i) == a[i]);
    }
    DynamicArray<int> test3(test2);
    assert(test3.GetSize() == test2.GetSize());
    for (int i = 0; i < test3.GetSize(); i++)
    {
        assert(test2.Get(i) == test3.Get(i));
    }
}
void TestDynamicArrayDecompositions()
{
    int a[] = {5, 4, 3, 2, 1};
    DynamicArray<int> test(a, 5);
    assert(test.Get(2) == a[2]);
    assert(test.GetSize() == 5);
}
void TestDynamicArrayOperations()
{
    int a[] = {5, 4, 3, 2, 1};
    DynamicArray<int> test(a, 5);
    assert(test.GetSize() == 5);
    for (int i = 0; i < test.GetSize(); i++)
    {
        assert(test.Get(i) == a[i]);
    }
    test.Set(6, 3);
    assert(test.Get(3) == 6);
    test.Resize(7);
    assert(test.GetSize() == 7);
}
void TestsDynamicArray()
{
    TestDynamicArrayConstructors();
    TestDynamicArrayDecompositions();
    TestDynamicArrayOperations();
}

#endif //TESTSDYNAMICARRAY_H
