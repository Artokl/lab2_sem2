#ifndef TESTSLISTSEQUENCE_H
#define TESTSLISTSEQUENCE_H

#include "ListSequence.h"
#include "assert.h"

void TestListSequenceConstructors()
{
    int a[6] = {1, 2, 3, 4, 5, 6};
    MutableListSequence<int> test1(a,6);
    assert(test1.GetLength() == 6);
    for (int i = 0; i < test1.GetLength(); i++)
    {
        assert(test1.Get(i) == a[i]);
    }
    ImmutableListSequence<int> test2(a,6);
    assert(test2.GetLength() == 6);
    for (int i = 0; i < test2.GetLength(); i++)
    {
        assert(test2.Get(i) == a[i]);
    }
    MutableListSequence<int> test3(test1);
    ImmutableListSequence<int> test4(test2);
    assert(test3.GetLength() == 6);
    assert(test4.GetLength() == 6);
    for (int i = 0; i < test3.GetLength(); i++)
    {
        assert(test3.Get(i) == a[i]);
        assert(test4.Get(i) == a[i]);
    }
    LinkedList<int> testAr1(a, 6);
    LinkedList<int> testAr2(a, 6);
    MutableListSequence<int> test5(testAr1);
    ImmutableListSequence<int> test6(testAr2);
    assert(test5.GetLength() == testAr1.GetLength());
    assert(test6.GetLength() == testAr2.GetLength());
    for (int i = 0; i < test5.GetLength(); i++)
    {
        assert(test5.Get(i) == testAr1.Get(i));
        assert(test6.Get(i) == testAr2.Get(i));
    }
}
void TestListSequenceDecompositions()
{
    int a[] = {5, 4, 3, 2, 1};
    MutableListSequence<int> test(a,5);
    assert(test.GetFirst() == 5);
    assert(test.GetLast() == 1);
    assert(test.Get(2) == 3);
    assert(test.GetLength() == 5);
    MutableListSequence<int> *test1 = test.GetSubSequence(2,4);
    for (int i = 0; i < test1->GetLength(); i++)
    {
        assert(test1->Get(i) == test.Get(i+2));
    }
    ImmutableListSequence<int> test2(a,5);
    assert(test2.GetFirst() == 5);
    assert(test2.GetLast() == 1);
    assert(test2.Get(2) == 3);
    assert(test2.GetLength() == 5);
    ImmutableListSequence<int> *test3 = test2.GetSubSequence(2,4);
    for (int i = 0; i < test3->GetLength(); i++)
    {
        assert(test3->Get(i) == test2.Get(i+2));
    }
}
void TestListSequenceOperations()
{
    int a[] = {5, 4, 3, 2, 1};
    int b[] = {1, 2, 3};
    int c[] = {5, 4, 3, 2, 1, 1, 2, 3};
    ImmutableListSequence<int> test(a,5);
    ImmutableListSequence<int> test1(b,3);
    ImmutableListSequence<int> *test2 = test.Concat(test1);
    for (int i = 0; i < test2->GetLength(); i++)
    {
        assert(test2->Get(i) == c[i]);
    }
    MutableListSequence<int> test3(a,5);
    MutableListSequence<int> test4(b,3);
    MutableListSequence<int> *test5 = test3.Concat(test4);
    for (int i = 0; i < test5->GetLength(); i++)
    {
        assert(test5->Get(i) == c[i]);
    }
    test3.Append(6);
    assert(test3.GetLast() == 6);
    test3.Prepend(7);
    assert(test3.GetFirst() == 7);
    test3.InsertAt(8,3);
    assert(test3.Get(3) == 8);
    ImmutableListSequence<int> *test6 = static_cast<ImmutableListSequence<int> *>(test.Append(6));
    assert(test6->GetLast() == 6);
    ImmutableListSequence<int> *test7 = static_cast<ImmutableListSequence<int> *>(test1.Prepend(7));
    assert(test7->GetFirst() == 7);
    ImmutableListSequence<int> *test8 = static_cast<ImmutableListSequence<int> *>(test1.InsertAt(8,2));
    assert(test8->Get(2) == 8);
}
void TestsListSequence()
{
    TestListSequenceConstructors();
    TestListSequenceDecompositions();
    TestListSequenceOperations();
}
#endif //TESTSLISTSEQUENCE_H
