#pragma once

#include <iostream>
#include <memory>

template <typename T>
struct Node {
    T data;
    std::unique_ptr<Node<T>> next;

//    explicit Node(const T& data) : data(data) {}
};

template <typename T>
class SingleLinkedList {
public:
    using NodePtr = std::unique_ptr<Node<T>>;

    void pushFront(const T& data) {
        auto newNode = std::make_unique<Node<T>>(data);
        newNode->next = std::move(head);
        head = std::move(newNode);
    }

    void pushBack(const T& data) {
        if (!head) {
            head = std::make_unique<Node<T>>(data);
            return;
        }

        auto current = head.get();

        while (current->next) current = current->next.get();

        current->next = std::make_unique<Node<T>>(data);
    }

    void popFront() {
        if (!head) return;

        head = std::move(head->next);
    }

    void popBack() {
        if (!head) return;

        if (!head->next) {
            head.reset();
            return;
        }

        auto current = head.get();

        while (current->next->next) {
            current = current->next.get();
        }

        current->next.reset();
    }

    [[nodiscard]]
    bool empty() const {
        return !head;
    }

    [[nodiscard]]
    T front() const {
        if (!head)
            throw std::out_of_range("List is empty");

        return head->data;
    }

    [[nodiscard]]
    T back() const {
        if (!head)
            throw std::out_of_range("List is empty");

        auto current = head.get();
        while (current->next) {
            current = current->next.get();
        }

        return current->data;
    }

    void print() const {
        auto current = head.get();

        while (current) {
            std::cout << current->data << " ";
            current = current->next.get();
        }

        std::cout << std::endl;
    }

private:
    NodePtr head = nullptr;
};
