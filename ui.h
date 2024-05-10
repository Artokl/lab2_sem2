#ifndef UI_H
#define UI_H
#include <iostream>
void startmenu()
{
    std::cout << "0. Stop programm\n";
    std::cout << "1. Run tests for DynamicArray\n";
    std::cout << "2. Run tests for LinkedList\n";
    std::cout << "3. Run tests for ArraySequence\n";
    std::cout << "4. Run tests for ListSequence\n";
}
void print(int status)
{
    if (status == 0) {
        std::cout << "Programm completed\n";
    }
    else if(status == 1) {
        std::cout << "Tests for DynamicArray passed\n";
    }
    else if(status == 2) {
        std::cout << "Tests for LinkedList passed\n";
    }
    else if(status == 3) {
        std::cout << "Tests for ArraySequence passed\n";
    }
    else if(status == 4) {
        std::cout << "Tests for ListSequence passed\n";
    }
    else {
        std::cout << "Unknown command\n";
    }

}
#endif //UI_H
