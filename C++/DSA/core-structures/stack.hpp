#pragma once
#include <iostream>
#include <stdexcept>

template <typename T> 
class Stack {
private:
    struct Node {
        T data;
        Node* next;

        Node(T val) : data(val), next(nullptr) {}
    };

    Node* top;
    int count; // contador para size().

public:
    Stack() : top(nullptr), count(0) {}
    ~Stack() { clear(); }

    void push(T value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
        count++;
    }

    bool empty() const { return top == nullptr; }

    void pop() { // elimina el nodo que se encuentre en el tope sin retornar sus datos.
        if (empty()) return;

        Node* auxPtr = top;
        top = top->next;
        delete auxPtr;
        count--;
    }

    // retorna una referencia modificable.
    T& peek() { 
        if (empty()) throw std::out_of_range("Empty Stack");
        return top->data;
    }

    // retorna una referencia constante (pila constante).
    const T& peek() const { 
        if (empty()) throw std::out_of_range("Empty Stack");
        return top->data;
    }

    int size() const { return count; }

    void clear() {
        while (top != nullptr) pop(); 
    }

    void print() const {
        Node* auxPtr = top;
        while(auxPtr != nullptr) {
            std::cout << "| " << auxPtr->data << " |\n";
            auxPtr = auxPtr->next;
        }
    } 
};

