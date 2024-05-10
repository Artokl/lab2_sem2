#ifndef TESTSLINKEDLIST_H
#define TESTSLINKEDLIST_H

#include "LinkedList.h"
#include "assert.h"

void TestLinkedListConstructors()
{
    int a[] = {5, 4, 3, 2, 1};
    LinkedList<int> test1(a, 5);
    assert(test1.GetLength() == 5);
    for (int i = 0; i < test1.GetLength(); i++)
    {
        assert(test1.Get(i) == a[i]);
    }
    LinkedList<int> test2(test1);
    assert(test2.GetLength() == test1.GetLength());
    for (int i = 0; i < test2.GetLength(); i++)
    {
        assert(test1.Get(i) == test2.Get(i));
    }
}
void TestLinkedListDecompositions()
{
    int a[] = {5, 4, 3, 2, 1};
    LinkedList<int> test1(a, 5);
    assert(test1.GetFirst() == a[0]);
    assert(test1.GetLast() == a[4]);
    assert(test1.Get(3) == a[3]);
    assert(test1.GetLength() == 5);
    LinkedList<int> *test2 = test1.GetSubList(2,4);
    for (int i = 0; i < test2->GetLength(); i++)
    {
        assert(test2->Get(i) == test1.Get(i+2));
    }
}
void TestLinkedListOperations()
{
    int a[] = {5, 4, 3, 2, 1};
    int b[] = {6, 7, 8};
    int c[] = {7, 5, 8, 4, 3, 2, 1, 6, 6, 7, 8};
    LinkedList<int> test(a, 5);
    test.Append(6);
    assert(test.GetLast() == 6);
    assert(test.GetLength() == 6);
    test.Prepend(7);
    assert(test.GetFirst() == 7);
    assert(test.GetLength() == 7);
    test.InsertAt(8,2);
    assert(test.GetLength() == 8);
    assert(test.Get(2) == 8);
    LinkedList<int> test1(b, 3);
    LinkedList<int> *test2 = test.Concat(test1);
    for (int i = 0; i < test2->GetLength(); i++)
    {
        assert(test2->Get(i) == c[i]);
    }
}
void TestsLinkedList()
{
    TestLinkedListConstructors();
    TestLinkedListDecompositions();
    TestLinkedListOperations();
}
#endif //TESTSLINKEDLIST_H
