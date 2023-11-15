#pragma once

#include <vector>
#include <stdexcept>

template <typename T>
class Stack {
public:
    void push(const T& value) {
        data.emplace_back(value);
    }

    T pop() {
        if (data.empty()) {
            throw std::out_of_range("Stack is empty");
        }

        const T topElement = data.back();
        data.pop_back();
        return topElement;
    }

    [[nodiscard]] bool empty() const {
        return data.empty();
    }

    const T& top() const {
        if (data.empty()) {
            throw std::out_of_range("Stack is empty");
        }

        return data.back();
    }

private:
    std::vector<T> data;
};

template <typename T, typename Comparator = std::less<T>>
class Heap {
public:
    void push(const T& value) {
        data.emplace_back(value);

        // Maintain heap property by sifting up the new element
        siftUp(data.size() - 1);
    }

    T pop() {
        if (data.empty()) {
            throw std::out_of_range("Heap is empty");
        }

        const T topElement = data.front();
        std::swap(data[0], data.back());
        data.pop_back();

        // Maintain heap property by sifting down the new top element
        siftDown(0);

        return topElement;
    }

    [[nodiscard]] bool empty() const {
        return data.empty();
    }

    const T& top() const {
        if (data.empty()) {
            throw std::out_of_range("Heap is empty");
        }

        return data.front();
    }

private:
    std::vector<T> data;
    Comparator comparator;

    void siftUp(size_t index) {
        while (index > 0) {
            size_t parentIndex = (index - 1) / 2;

            if (!comparator(data[index], data[parentIndex])) {
                break;
            }

            std::swap(data[index], data[parentIndex]);
            index = parentIndex;
        }
    }

    void siftDown(size_t index) {
        size_t leftIndex = index * 2 + 1;
        size_t rightIndex = leftIndex + 1;

        size_t childIndex = index;

        if (leftIndex < data.size() && comparator(data[index], data[leftIndex])) {
            childIndex = leftIndex;
        }

        if (rightIndex < data.size() && comparator(data[childIndex], data[rightIndex])) {
            childIndex = rightIndex;
        }

        if (childIndex != index) {
            std::swap(data[index], data[childIndex]);
            siftDown(childIndex);
        }
    }
};
