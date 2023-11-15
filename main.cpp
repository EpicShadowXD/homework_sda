#include <iostream>
#include <algorithm>
#include <ranges>

//#include "sorts.h"
//#include "SingleLinkedLists.h"
//#include "DoublyLinkedLists.h"
#include "StackAndHeap.h"

int main() {
//    std::vector numbers{5, 2, 1, 7, 9, 4, 3, 8};
//
//    std::ranges::copy(numbers | std::ranges::views::all,
//                      std::ostream_iterator<decltype(numbers.at(0))>(std::cout, " "));

//    SingleLinkedList<int> list;
//    std::ranges::for_each(std::views::iota(1, 11), [&list](int value) {
//        list.pushFront(value);
//    });
//    list.print();

    // does not work, too lazy to fix
//    DoublyLinkedList<int> list;
//    list.pushFront(1);

//    Stack<int> stack;
//    std::ranges::for_each(std::views::iota(1, 11), [&stack](int value) {
//        stack.push(value);
//    });
//    while (!stack.empty()) {
//        std::cout << stack.top() << ' ';
//        stack.pop();
//    }

    Heap<int> heap;
    std::ranges::for_each(std::views::iota(1, 11), [&heap](int value) {
        heap.push(value);
    });
    while (!heap.empty()) {
        std::cout << heap.pop() << ' ';
    }
}
