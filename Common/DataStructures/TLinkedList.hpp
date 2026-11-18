#pragma once
#include <stdexcept> // For std::runtime_error
#include <string>    // For std::to_string
#include <functional> // For std::function
#include "../DebugUtils.h" // For debugText function
#include "TCollection.hpp" // Your base collection class
#include "TNode.hpp" // Your node class

/**
* @file   TLinkedList.hpp
* @brief  Dear student, this file contains the definition of the TLinkedList class template, which serves as a doubly-linked list implementation for storing elements of type T.
*					You will create this as a template class typically holding methods for appending, prepending, searching, and iterating over elements.
*					Type of linked list is op to you, you must clean (delete) your data yourself so be wize about the type of T you choose to use.
*         I recommend to implenet a "isOwner" boolean variable to determine if the list is responsible for deleting the data or not.
*					Please ask for help in Discord if you have any questions or need assistance with the implementation.
* @tparam T The type of elements stored in the linked list.
*/

template<typename T>
class TLinkedList {
public:
    TLinkedList(bool ownsData);
    ~TLinkedList();

    TLinkedList* GetHead();
    TLinkedList* GetTail();

    void Append(T* data);       // Creates new node with the data at the back of the list
    void Prepend(T* data);      // Creates new node with the data at the front of the list
private:
    TNode<T>* head;             // Pointer to front of list
    TNode<T>* tail;             // Pointer to back of list
    bool isOwner;               // Determines if the list is responsible for handling the data
};

// Constructor that creates a list of a front and back dummy node
template<typename T>
TLinkedList<T>::TLinkedList(const bool ownsData) : isOwner(ownsData) {
    // Creates dummy nodes at front and back and links them
    head = new TNode<T>(nullptr, nullptr, nullptr);
    tail = new TNode<T>(nullptr, head, nullptr);
    head->next = tail;
}

// Destructor iterates through every node in the list and deletes them. Will only delete data if ownsData is true.
template<typename T>
TLinkedList<T>::~TLinkedList() {
    TNode<T>* current = head;

    while (current) {
        TNode<T> *next = current->GetNext();        // Points to next node in list to keep track
        if (isOwner) delete current->GetData();    // Deletes data if list owns it
        delete current;                             // Deletes node
        current = next;                             // Iterates the node to be deleted
    }
}

template<typename T>
TLinkedList<T> *TLinkedList<T>::GetHead() {
    return head;
}

template<typename T>
TLinkedList<T>* TLinkedList<T>::GetTail() {
    return tail;
}

template<typename T>
void TLinkedList<T>::Append(T* data) {
    // Creates new node with correct pointers
    TNode<T>* newNode = new TNode<T>(data, tail->GetPrev(), tail);

    // Updates pointers of adjacent nodes
    newNode->GetPrev()->SetNext(newNode); // Sets pointer of previous node
    tail->SetPrev(newNode); // Sets pointer of next node (tail)
}

template<typename T>
void TLinkedList<T>::Prepend(T* data) {
    // Creates new node with correct pointers
    TNode<T>* newNode = new TNode<T>(data, head, head->GetNext());

    // Updates pointers of adjacent nodes
    head->SetNext(newNode); // Sets pointer of previous node (head)
    newNode->GetNext()->SetPrev(newNode); // Sets pointer of next node
}

