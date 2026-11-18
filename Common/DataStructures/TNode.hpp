/**
* @file TNode.hpp
* @brief  Dear student, this file contains the definition of the TNode class template, which serves as a node in a doubly-linked list implementation for storing elements of type T.
*					You will create this as a template class typically holding data of type T and pointers to other nodes in the list. (you must choose if this is singel or double linked list)
*					Please ask for help in Discord if you have any questions or need assistance with the implementation.
*/

// This is a node for a doubly linked list
template<typename T>
class TNode {
public:
    TNode(T* data, TNode* prev, TNode* next);
    ~TNode();

private:
    T* data;
    TNode* prev;
    TNode* next;
};

// Constructs node that points to object of datatype T
template<typename T>
TNode<T>::TNode(T* data, TNode* prev, TNode* next)
    : data(data), prev(prev), next(next) {}

// Constructor that does nothing :)
template<typename T>
TNode<T>::~TNode() {}