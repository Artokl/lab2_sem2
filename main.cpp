#include <iostream>
#include "TestsDynamicArray.h"
#include "TestsLinkedList.h"
#include "TestsArraySequence.h"
#include "TestsListSequence.h"
#include "Ui.h"

int main() {
    int status = 0;
    int flag = 1;
    startmenu();
    while (flag) {
        std::cin >> status;
        switch (status)
        {
            case 0:
            {
                flag = 0;
                print(status);
                break;
            }
            case 1:
            {
                TestsDynamicArray();
                print(status);
                break;
            }
            case 2:
            {
                TestsLinkedList();
                print(status);
                break;
            }
            case 3:
            {
                TestsArraySequence();
                print(status);
                break;
            }
            case 4:
            {
                TestsListSequence();
                print(status);
                break;
            }
            default:
            {
                print(status);
                break;
            }
        }
        if (status != 0)
        {
            startmenu();
        }
    }
    return 0;
}
