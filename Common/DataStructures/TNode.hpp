/**
* @file TNode.hpp
* @brief  Dear student, this file contains the definition of the TNode class template, which serves as a node in a doubly-linked list implementation for storing elements of type T.
*					You will create this as a template class typically holding data of type T and pointers to other nodes in the list. (you must choose if this is singel or double linked list)
*					Please ask for help in Discord if you have any questions or need assistance with the implementation.
*/

// This is a node for a doubly linked list
#pragma once

template<typename T>
class TNode {
public:
    TNode(T* data, TNode* prev, TNode* next);
    ~TNode();

    void SetData(T* data);          // Sets data as input pointer
    T* GetData();                   // Returns a pointer to the data

    void SetPrev(TNode* prev);      // Sets previous as input pointer
    TNode* GetPrev();               // Returns pointer to previous node

    void SetNext(TNode* next);      // Sets next as input pointer
    TNode* GetNext();               // Returns pointer to next node

private:
    T* data;
    TNode* prev;
    TNode* next;
};

// Constructs node that points to object of datatype T
template<typename T>
TNode<T>::TNode(T* data, TNode* prev, TNode* next)
    : data(data), prev(prev), next(next) {}

// Destructor that does nothing special
template<typename T>
TNode<T>::~TNode() {}


template<typename T>
void TNode<T>::SetData(T* data) {this->data = data;}

template<typename T>
T* TNode<T>::GetData() {return this->data;}


template<typename T>
void TNode<T>::SetPrev(TNode* prev) {this->prev = prev;}

template<typename T>
TNode<T>* TNode<T>::GetPrev() {return this->prev;}


template<typename T>
void TNode<T>::SetNext(TNode* next) {this->next = next;}

template<typename T>
TNode<T>* TNode<T>::GetNext() {return this->next;}