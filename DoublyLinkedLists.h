#pragma once

#include <iostream>
#include <memory>
#include <iostream>
#include <memory>

template <typename T>
class Node {
public:
    T data;
    std::unique_ptr<Node<T>> prev{nullptr};
    std::unique_ptr<Node<T>> next{nullptr};

//    Node(T value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
private:
    std::unique_ptr<Node<T>> head{nullptr};
    Node<T>* tail{nullptr}; // Does not own

public:
//    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void pushBack(const T& data) {
        auto newNode = std::make_unique<Node<T>>(data);
        if (!head) {
            head = std::move(newNode);
            tail = head.get();
        } else {
            newNode->prev = std::move(tail->next);  // Transfer ownership
            tail->next = std::move(newNode);
            tail = tail->next.get();
        }
    }

    void pushFront(const T& data) {
        auto newNode = std::make_unique<Node<T>>(data);
        if (!head) {
            head = std::move(newNode);
            tail = head.get();
        } else {
            newNode->next = std::move(head);
            head->prev = std::make_unique<Node<T>>(*newNode);  // Transfer ownership
            head = std::move(newNode);
        }
    }


    void deleteNode(const T& data) {
        Node<T>* current = head.get();

        while (current) {
            if (current->data == data) {
                if (current->prev) {
                    current->prev->next = std::move(current->next);
                    if (current->next) {
                        current->next->prev = std::move(current->prev);
                    } else {
                        tail = current->prev.get();
                    }
                } else {
                    head = std::move(current->next);
                    if (head) {
                        head->prev = nullptr;
                    }
                }

                return;
            }

            current = current->next.get();
        }

        std::cerr << "Node with value " << data << " not found.\n";
    }

    void print() const {
        Node<T>* current = head.get();
        while (current) {
            std::cout << current->data << " ";
            current = current->next.get();
        }
        std::cout << std::endl;
    }
};