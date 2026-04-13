#pragma once
#include <iostream>
#include <stdexcept>

template <typename T> 
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* frontNode;
    Node* backNode;
    int count; // contador para size().

public:
    Queue() : frontNode(nullptr), backNode(nullptr), count(0) {}
    ~Queue() { clear(); }

    bool empty() const { return frontNode == nullptr; }

    void enqueue(T value) {
        Node* newNode = new Node(value);
        if (empty()) {
            frontNode = backNode = newNode;
        } else {
            backNode->next = newNode;
            backNode = newNode;
        }
        count++;
    }

    void dequeue() { // elimina el nodo que se encuentre en el frente sin retornar sus datos.
        if (empty()) return;

        Node* auxPtr = frontNode;
        frontNode = frontNode->next;
        delete auxPtr;
        count--;

        if (empty()) backNode = nullptr;
    }

    // retorna una referencia modificable de *front.
    T& front() { 
        if (empty()) throw std::out_of_range("Empty Queue");
        return frontNode->data;
    }

    // retorna una referencia no modificable de *front.
    const T& front() const { 
        if (empty()) throw std::out_of_range("Empty Queue");
        return frontNode->data;
    }

    // retorna una referencia modificable de *back;
    T& back() { 
        if (empty()) throw std::out_of_range("Empty Queue");
        return backNode->data;
    }

    // retorna una referencia no modificable de *back;
    const T& back() const { 
        if (empty()) throw std::out_of_range("Empty Queue");
        return backNode->data;
    }

    int size() const { return count; }

    void clear() {
        while (frontNode != nullptr) dequeue();
    }

    void print() const {
        Node* auxPtr = frontNode;
        std::cout << "{ ";
        while(auxPtr != nullptr) {
            std::cout << auxPtr->data;
            if (auxPtr->next != nullptr) std::cout << ", ";
            auxPtr = auxPtr->next;
        }
        std::cout << " }\n";
    } 
};
