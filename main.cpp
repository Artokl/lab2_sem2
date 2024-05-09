#include <iostream>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "Sequence.h"



int main() {
    int A[] = {1, 2, 3, 4};
    DynamicArray<int> B (A,4);
    LinkedList<int> C(A, 4);
    C.InsertAt(9,2);
    std::cout << C.Get(2) << std::endl;
    std::cout << C.GetLength() << std::endl;
    B.Resize(3);
    std::cout << B.GetSize() << std::endl;
    std::cout << B.Get(2) << std::endl;
    return 0;
}
