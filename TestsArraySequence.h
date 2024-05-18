#ifndef TESTSARRAYSEQUENCE_H
#define TESTSARRAYSEQUENCE_H

#include "ArraySequence.h"
#include "assert.h"

void TestArraySequenceConstructors()
{
    int a[6] = {1, 2, 3, 4, 5, 6};
    MutableArraySequence<int> test1(a,6);
    assert(test1.GetLength() == 6);
    for (int i = 0; i < test1.GetLength(); i++)
    {
        assert(test1.Get(i) == a[i]);
    }
    ImmutableArraySequence<int> test2(a,6);
    assert(test2.GetLength() == 6);
    for (int i = 0; i < test2.GetLength(); i++)
    {
        assert(test2.Get(i) == a[i]);
    }
    MutableArraySequence<int> test3(test1);
    ImmutableArraySequence<int> test4(test2);
    assert(test3.GetLength() == 6);
    assert(test4.GetLength() == 6);
    for (int i = 0; i < test3.GetLength(); i++)
    {
        assert(test3.Get(i) == a[i]);
        assert(test4.Get(i) == a[i]);
    }
    DynamicArray<int> testAr1(a, 6);
    DynamicArray<int> testAr2(a, 6);
    MutableArraySequence<int> test5(testAr1);
    ImmutableArraySequence<int> test6(testAr2);
    assert(test5.GetLength() == testAr1.GetSize());
    assert(test6.GetLength() == testAr2.GetSize());
    for (int i = 0; i < test5.GetLength(); i++)
    {
        assert(test5.Get(i) == testAr1.Get(i));
        assert(test6.Get(i) == testAr2.Get(i));
    }
}
void TestArraySequenceDecompositions()
{
    int a[5] = {5, 4, 3, 2, 1};
    MutableArraySequence<int> test1(a,5);
    assert(test1.GetFirst() == 5);
    assert(test1.GetLast() == 1);
    assert(test1.GetLength() == 5);
    assert(test1.Get(2) == a[2]);
    MutableArraySequence<int> *test2 = test1.GetSubSequence(2,4);
    for (int i = 0; i < test2->GetLength(); i++)
    {
        assert(test2->Get(i) == test1.Get(i+2));
    }
    ImmutableArraySequence<int> test3(a,5);
    assert(test3.GetFirst() == 5);
    assert(test3.GetLast() == 1);
    assert(test3.GetLength() == 5);
    assert(test3.Get(2) == a[2]);
    ImmutableArraySequence<int> *test4 = test3.GetSubSequence(2,4);
    for (int i = 0; i < test4->GetLength(); i++)
    {
        assert(test4->Get(i) == test3.Get(i+2));
    }
}
void TestArraySequenceOperations()
{
    int a[5] = {5, 4, 3, 2, 1};
    int b[3] = {8, 9, 10};
    int c[] = {5, 4, 3, 2, 1, 8, 9, 10};
    MutableArraySequence<int> test(a,5);
    MutableArraySequence<int> test1(b,3);
    MutableArraySequence<int> *test2 = test.Concat(test1);
    for (int i = 0; i < test2->GetLength(); i++)
    {
        assert(test2->Get(i) == c[i]);
    }
    test.Append(6);
    assert(test.GetLast() == 6);
    test.Prepend(7);
    assert(test.GetFirst() == 7);
    test.InsertAt(8,3);
    assert(test.Get(3) == 8);
    ImmutableArraySequence<int> test3(a,5);
    ImmutableArraySequence<int> test4(b,3);
    ImmutableArraySequence<int> *test5 = test3.Concat(test4);
    for (int i = 0; i < test5->GetLength(); i++)
    {
        assert(test5->Get(i) == c[i]);
    }
    ImmutableArraySequence<int> *test6 = static_cast<ImmutableArraySequence<int> *>(test3.Append(6));
    assert(test6->GetLast() == 6);
    ImmutableArraySequence<int> *test7 = static_cast<ImmutableArraySequence<int> *>(test4.Prepend(7));
    assert(test7->GetFirst() == 7);
    ImmutableArraySequence<int> *test8 = static_cast<ImmutableArraySequence<int> *>(test3.InsertAt(8,2));
    assert(test8->Get(2) == 8);

}
void TestsArraySequence()
{
    TestArraySequenceConstructors();
    TestArraySequenceDecompositions();
    TestArraySequenceOperations();
}

#endif //TESTSARRAYSEQUENCE_H

