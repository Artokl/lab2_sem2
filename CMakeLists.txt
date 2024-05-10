cmake_minimum_required(VERSION 3.28)
project(lab_2)

set(CMAKE_CXX_STANDARD 11)

add_executable(lab_2 main.cpp
        DynamicArray.h
        LinkedList.h
        Sequence.h
        ArraySequence.h
        ListSequence.h
        TestsDynamicArray.h
        TestsLinkedList.h
        TestsArraySequence.h
        TestsListSequence.h
        ui.h)
