#pragma once
#include "TCollection.hpp" // This is your base class for collections
#include "TLinkedList.hpp" // This is your linked list implementation
#include "DebugUtils.h" // This is the provided debug utility for logging
#include <stdexcept> // This is for throwing exceptions when needed


/**
* @file   TStack.hpp
* @brief  Dear student, this file contains the definition of the TStack class template, which serves as a stack implementation for storing elements of type T.
*         Be aware that this stack is implemented using a linked list, and it does not own the data it stores.
*         You will create this as a template class typically holding methods for pushing, popping, peeking, and checking the size of the stack.
*         Please ask for help in Discord if you have any questions or need assistance with the implementation.
*/

template <typename T>
class TStack : TCollection<T> {
public:
    TStack();
    ~TStack();

    void Push(T data);
    T* Pop();
    T* Peek();
    void Clear() override;
private:
    TNode<T>* head;
};

template <typename T>
TStack<T>::TStack() {
    head = new TNode<T>(nullptr, nullptr, nullptr);
    head->SetNext(new TNode<T>(nullptr, head, nullptr)); // Tail dummy node w/o pointer
}

template <typename T>
TStack<T>::~TStack() {
    TNode<T>* current = head;

    while (current) {
        TNode<T> *next = current->GetNext();        // Points to next node in list to keep track
        delete current;                             // Deletes node
        current = next;                             // Iterates the node to be deleted
    }
}

template <typename T>
void TStack<T>::Push(T data) {
    auto newNode = new TNode<T>(data, head, head->GetNext()); // Create new node with data

    // Adjust pointers
    newNode->GetNext()->SetPrev(newNode);
    head->SetNext(newNode);
}

template <typename T>
T* TStack<T>::Pop() {
    // Get Node
    TNode<T>* node = head->GetNext();

    // Adjust Pointers
    head->SetNext(node->GetNext());
    node->GetNext()->SetPrev(head);

    // Keeps track of data after the node has been deleted
    T* nodeData = node->GetData();

    // Remove node
    delete node;

    // Get data
    return nodeData;
}

template <typename T>
T* TStack<T>::Peek() {
    return head->GetNext()->GetData();
}

template <typename T>
void TStack<T>::Clear() {
    TNode<T>* current = head->GetNext();

    while (current->GetData() != nullptr) { // Checks for dummy tail node
        TNode<T> *next = current->GetNext();        // Points to next node in list to keep track
        delete current;                             // Deletes node
        current = next;                             // Iterates the node to be deleted
    }
}