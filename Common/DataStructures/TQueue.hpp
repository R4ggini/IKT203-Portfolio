#pragma once
#include "TCollection.hpp" // This is your base class for collections
#include "TNode.hpp" // This is your node implementation
#include "DebugUtils.h" // This is the provided debug utility for logging
#include <stdexcept> // This is for throwing exceptions when needed

/**
* @file   TQueue.hpp
* @brief  Dear student, this file contains the definition of the TQueue class template, which serves as a queue implementation for storing elements of type T.
*         Be aware that this queue is implemented using a linked list, and it does not own the data it stores.
*         You will create this as a template class typically holding methods for enqueueing, dequeueing, peeking, and checking the size of the queue.
*         Please ask for help in Discord if you have any questions or need assistance with the implementation.
*/

// Class for creating linked lists strictly enforcing FIFO rules.
// Does not own any data.
template<typename T>
class TQueue : public TCollection<T> {
public:
    TQueue();
    ~TQueue();

    void Enqueue(T* data);  // Adds data to back of queue
    T* Dequeue();           // Returns data of first node in list

    void Clear() override;  // Removes all data nodes in list
private:
    TNode<T>* head;         // Pointer to first node in list
    TNode<T>* tail;         // Pointer to last node in list
};

// Creates an empty linked list with dummy nodes
template<typename T>
TQueue<T>::TQueue() {
    // Creates dummy nodes at front and back and links them
    head = new TNode<T>(nullptr, nullptr, nullptr);
    tail = new TNode<T>(nullptr, head, nullptr);
    head->SetNext(tail);
}

template<typename T>
TQueue<T>::~TQueue() {
    TNode<T>* current = head;

    while (current) {
        TNode<T> *next = current->GetNext();        // Points to next node in list to keep track
        delete current;                             // Deletes node
        current = next;                             // Iterates the node to be deleted
    }
}

template<typename T>
void TQueue<T>::Enqueue(T* data) {
    // Keeps size consistent
    ++this->size;

    // Creates new node before tail
    auto* newNode = new TNode<T>(data, tail->GetPrev(), tail);

    // Modifies pointers on adjacent nodes to point correctly
    newNode->GetPrev()->SetNext(newNode);
    tail->SetPrev(newNode);
}

template<typename T>
T* TQueue<T>::Dequeue() {
    // Keeps size consistent
    if (this->IsEmpty()) return nullptr;
    --this->size;

    // Gets first node
    TNode<T>* firstNode = head->GetNext();

    // Modifies pointers of adjacent nodes
    head->SetNext(firstNode->GetNext());
    firstNode->GetNext()->SetPrev(head);

    // Gets data of node
    T* firstNodeData = firstNode->GetData();

    // Deletes node
    delete firstNode;

    return firstNodeData; // Returns data from node
}

// Removes every node in a list except for dummy nodes
template<typename T>
void TQueue<T>::Clear() {
    TNode<T>* current = head->GetNext();

    while (current != tail) { // Same logic as TLinkedList Clear method
        TNode<T> *next = current->GetNext();        // Points to next node in list to keep track
        delete current;                             // Deletes node
        current = next;                             // Iterates the node to be deleted
    }

    // Correct pointers and size
    head->SetNext(tail);
    tail->SetPrev(head);
    this->size = 0;
}
