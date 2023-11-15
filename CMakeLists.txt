cmake_minimum_required(VERSION 3.26)
project(tema_asd)

set(CMAKE_CXX_STANDARD 23)

add_executable(tema_asd main.cpp
        sorts.h
        SingleLinkedLists.h
        DoublyLinkedLists.h
        StackAndHeap.h)
